#include "Order.h"
#include "DatabaseManager.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

// ==================== OrderItem ====================

OrderItem::OrderItem(int itemId, int orderId, int productId, int quantity, double totalPrice)
    : itemId(itemId), orderId(orderId), productId(productId),
      quantity(quantity), totalPrice(totalPrice) {
    if (quantity <= 0) {
        throw std::invalid_argument("Quantity must be positive");
    }
    if (totalPrice < 0) {
        throw std::invalid_argument("Total price cannot be negative");
    }
}

void OrderItem::display() const {
    std::cout << "  Item ID: " << itemId
              << " | Product ID: " << productId
              << " | Quantity: " << quantity
              << " | Total: $" << std::fixed << std::setprecision(2) << totalPrice
              << std::endl;
}

bool OrderItem::addItemToOrder(int orderId, int productId, int quantity) {
    auto& db = DatabaseManager::getInstance();

    try {
        // Начинаем транзакцию
        pqxx::work txn(db.getConnection());

        // 1. Проверяем существование заказа
        pqxx::result orderCheck = txn.exec(
            "SELECT 1 FROM orders WHERE order_id = " + txn.quote(orderId)
        );
        if (orderCheck.empty()) {
            db.logOperation("ERROR", "Order " + std::to_string(orderId) + " does not exist");
            return false;
        }

        // 2. Проверяем существование товара и получаем цену
        pqxx::result productCheck = txn.exec(
            "SELECT price FROM products WHERE id = " + txn.quote(productId) +
            " AND id NOT IN (SELECT product_id FROM order_items WHERE order_id = " +
            txn.quote(orderId) + ")"
        );
        if (productCheck.empty()) {
            db.logOperation("ERROR", "Product " + std::to_string(productId) +
                           " does not exist or already in order");
            return false;
        }

        double price = productCheck[0]["price"].as<double>();
        double totalPrice = price * quantity;

        // 3. Вставляем позицию заказа
        std::string query =
            "INSERT INTO order_items (order_id, product_id, quantity, total_price) "
            "VALUES (" + txn.quote(orderId) + ", " +
            txn.quote(productId) + ", " +
            txn.quote(quantity) + ", " +
            txn.quote(totalPrice) + ") RETURNING order_item_id";

        pqxx::result res = txn.exec(query);
        txn.commit();

        int newItemId = res[0]["order_item_id"].as<int>();
        db.logOperation("ADD_ITEM",
                       "Added item ID " + std::to_string(newItemId) +
                       " to order " + std::to_string(orderId));

        return true;

    } catch (const std::exception& e) {
        // Транзакция автоматически откатывается при исключении
        db.logOperation("ERROR", std::string("Add item failed: ") + e.what());
        return false;
    }
}

std::vector<OrderItem> OrderItem::getItemsByOrder(int orderId) {
    std::vector<OrderItem> items;
    auto& db = DatabaseManager::getInstance();

    try {
        pqxx::work txn(db.getConnection());

        std::string query =
            "SELECT order_item_id, order_id, product_id, quantity, total_price "
            "FROM order_items WHERE order_id = " + txn.quote(orderId) +
            " ORDER BY order_item_id";

        pqxx::result res = txn.exec(query);

        for (const auto& row : res) {
            OrderItem item(
                row["order_item_id"].as<int>(),
                row["order_id"].as<int>(),
                row["product_id"].as<int>(),
                row["quantity"].as<int>(),
                row["total_price"].as<double>()
            );
            items.push_back(item);
        }

        db.logOperation("READ", "Retrieved " + std::to_string(items.size()) +
                       " items for order " + std::to_string(orderId));

    } catch (const std::exception& e) {
        db.logOperation("ERROR", std::string("Get items failed: ") + e.what());
    }

    return items;
}

bool OrderItem::removeItemFromOrder(int itemId) {
    auto& db = DatabaseManager::getInstance();

    try {
        pqxx::work txn(db.getConnection());

        txn.exec("DELETE FROM order_items WHERE order_item_id = " + txn.quote(itemId));
        txn.commit();

        db.logOperation("DELETE_ITEM", "Deleted item ID: " + std::to_string(itemId));
        return true;

    } catch (const std::exception& e) {
        db.logOperation("ERROR", std::string("Delete item failed: ") + e.what());
        return false;
    }
}

// ==================== Order ====================

Order::Order(int orderId, const std::string& date)
    : orderId(orderId), orderDate(date) {}

int Order::createOrder(const std::string& date) {
    auto& db = DatabaseManager::getInstance();

    try {
        pqxx::work txn(db.getConnection());

        std::string query = "INSERT INTO orders (order_date) VALUES (";
        if (date.empty()) {
            query += "CURRENT_DATE";
        } else {
            query += txn.quote(date);
        }
        query += ") RETURNING order_id";

        pqxx::result res = txn.exec(query);
        txn.commit();

        int newOrderId = res[0]["order_id"].as<int>();
        db.logOperation("CREATE_ORDER", "Created order ID: " + std::to_string(newOrderId));

        return newOrderId;

    } catch (const std::exception& e) {
        db.logOperation("ERROR", std::string("Create order failed: ") + e.what());
        return -1;
    }
}

Order Order::getOrderById(int orderId) {
    auto& db = DatabaseManager::getInstance();

    try {
        pqxx::work txn(db.getConnection());

        std::string query =
            "SELECT order_id, order_date FROM orders WHERE order_id = " +
            txn.quote(orderId);

        pqxx::result res = txn.exec(query);

        if (res.empty()) {
            throw std::runtime_error("Order not found");
        }

        auto row = res[0];
        Order order(
            row["order_id"].as<int>(),
            row["order_date"].c_str()
        );

        // Загружаем элементы заказа
        auto items = OrderItem::getItemsByOrder(orderId);
        for (const auto& item : items) {
            order.addItem(item);
        }

        db.logOperation("READ", "Retrieved order ID: " + std::to_string(orderId));
        return order;

    } catch (const std::exception& e) {
        db.logOperation("ERROR", std::string("Get order failed: ") + e.what());
        throw;
    }
}

std::vector<Order> Order::getAllOrders() {
    std::vector<Order> orders;
    auto& db = DatabaseManager::getInstance();

    try {
        pqxx::work txn(db.getConnection());

        std::string query =
            "SELECT order_id, order_date FROM orders ORDER BY order_date DESC, order_id";

        pqxx::result res = txn.exec(query);

        for (const auto& row : res) {
            Order order(
                row["order_id"].as<int>(),
                row["order_date"].c_str()
            );
            orders.push_back(order);
        }

        db.logOperation("READ", "Retrieved " + std::to_string(orders.size()) + " orders");

    } catch (const std::exception& e) {
        db.logOperation("ERROR", std::string("Get all orders failed: ") + e.what());
    }

    return orders;
}

bool Order::deleteOrder(int orderId) {
    auto& db = DatabaseManager::getInstance();

    try {
        pqxx::work txn(db.getConnection());

        txn.exec("DELETE FROM orders WHERE order_id = " + txn.quote(orderId));
        txn.commit();

        db.logOperation("DELETE_ORDER", "Deleted order ID: " + std::to_string(orderId));
        return true;

    } catch (const std::exception& e) {
        db.logOperation("ERROR", std::string("Delete order failed: ") + e.what());
        return false;
    }
}

double Order::calculateTotal() const {
    double total = 0.0;
    for (const auto& item : items) {
        total += item.getTotalPrice();
    }
    return total;
}

void Order::display() const {
    std::cout << "\n=== Order #" << orderId << " ===" << std::endl;
    std::cout << "Date: " << orderDate << std::endl;
    std::cout << "Items:" << std::endl;

    for (const auto& item : items) {
        item.display();
    }

    std::cout << "Total: $" << std::fixed << std::setprecision(2) << calculateTotal()
              << "\n" << std::endl;
}