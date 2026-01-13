#include "Users.h"
#include <fstream>


static auto canSeeAudit = [](const User& u){
    return u.role() == "admin";
};

static auto canChangeOrderStatus = [](const User& u){
    return u.role() == "admin" || u.role() == "manager";
};


void Admin::addProduct(DatabaseConnection<std::string>& db, const Product& p) {
    try {
        db.beginTransaction();
        db.setAppUserId(this->id());

        db.executeNonQuery(
            "INSERT INTO products(name, price, stock_quantity) VALUES (" +
            db.quote(p.name) + ", " + std::to_string(p.price) + ", " + std::to_string(p.stock) + ");"
        );

        db.commitTransaction();
    } catch (const std::exception& e) {
        db.rollbackTransaction();
        db.executeNonQuery(
            "INSERT INTO audit_log(entity_type, entity_id, operation, performed_by, details) VALUES "
            "('product', -1, 'error', " + std::to_string(this->id()) + ", " + db.quote(e.what()) + ");"
        );
        throw;
    }
}

void Admin::updateProduct(DatabaseConnection<std::string>& db, const Product& p) {
    try {
        db.beginTransaction();
        db.setAppUserId(this->id());

        db.executeNonQuery(
            "UPDATE products SET name=" + db.quote(p.name) +
            ", price=" + std::to_string(p.price) +
            ", stock_quantity=" + std::to_string(p.stock) +
            " WHERE product_id=" + std::to_string(p.id) + ";"
        );

        db.commitTransaction();
    } catch (const std::exception& e) {
        db.rollbackTransaction();
        db.executeNonQuery(
            "INSERT INTO audit_log(entity_type, entity_id, operation, performed_by, details) VALUES "
            "('product', " + std::to_string(p.id) + ", 'error', " + std::to_string(this->id()) + ", " + db.quote(e.what()) + ");"
        );
        throw;
    }
}

void Admin::deleteProduct(DatabaseConnection<std::string>& db, int productId) {
    try {
        db.beginTransaction();
        db.setAppUserId(this->id());

        db.executeNonQuery("DELETE FROM products WHERE product_id=" + std::to_string(productId) + ";");

        db.commitTransaction();
    } catch (const std::exception& e) {
        db.rollbackTransaction();
        db.executeNonQuery(
            "INSERT INTO audit_log(entity_type, entity_id, operation, performed_by, details) VALUES "
            "('product', " + std::to_string(productId) + ", 'error', " + std::to_string(this->id()) + ", " + db.quote(e.what()) + ");"
        );
        throw;
    }
}

void Admin::viewAllOrders(DatabaseConnection<std::string>& db) {
    auto rows = db.executeQuery("SELECT order_id, user_id, status, total_price, order_date FROM orders ORDER BY order_id;");
    for (const auto& r : rows) {
        std::cout << "Order #" << r[0] << " user=" << r[1] << " status=" << r[2]
                  << " total=" << r[3] << " date=" << r[4] << "\n";
    }
}

void Admin::updateOrderStatus(DatabaseConnection<std::string>& db, int orderId, const std::string& newStatus) {
    if (!canChangeOrderStatus(*this)) throw std::runtime_error("Access denied");

    try {
        db.beginTransaction();
        db.setAppUserId(this->id());


        db.executeNonQuery(
            "CALL updateOrderStatus(" + std::to_string(orderId) + ", " + db.quote(newStatus) + ", " + std::to_string(this->id()) + ");"
        );

        db.commitTransaction();
    } catch (const std::exception& e) {
        db.rollbackTransaction();
        db.executeNonQuery(
            "INSERT INTO audit_log(entity_type, entity_id, operation, performed_by, details) VALUES "
            "('order', " + std::to_string(orderId) + ", 'error', " + std::to_string(this->id()) + ", " + db.quote(e.what()) + ");"
        );
        throw;
    }
}


std::shared_ptr<Order> Admin::createOrder(DatabaseConnection<std::string>&) {
    auto o = std::make_shared<Order>(-1, this->id());
    attachOrder(o);
    return o;
}

std::string Admin::viewOrderStatus(DatabaseConnection<std::string>& db, int orderId) {
    auto r = db.executeQuery("SELECT getOrderStatus(" + std::to_string(orderId) + ");");
    return r.at(0).at(0);
}

void Admin::cancelOrder(DatabaseConnection<std::string>& db, int orderId) {
    updateOrderStatus(db, orderId, "canceled");
}

void Admin::exportCsvReport(DatabaseConnection<std::string>& db, const std::string& path) {
    if (!canSeeAudit(*this)) throw std::runtime_error("Access denied");

    auto rows = db.executeQuery("SELECT * FROM getAuditOrderReport();");

    std::ofstream out(path);
    if (!out) throw std::runtime_error("Cannot open CSV file for writing");


    for (const auto& r : rows) {
        for (size_t i = 0; i < r.size(); ++i) {
            if (i) out << ",";

            std::string cell = r[i];
            bool needQuotes = cell.find(',') != std::string::npos || cell.find('"') != std::string::npos;
            if (needQuotes) {
                std::string escaped;
                for (char c : cell) escaped += (c == '"' ? "\"\"" : std::string(1, c));
                out << "\"" << escaped << "\"";
            } else out << cell;
        }
        out << "\n";
    }
}


void Manager::approveOrder(DatabaseConnection<std::string>& db, int orderId) {
    if (!canChangeOrderStatus(*this)) throw std::runtime_error("Access denied");


    db.beginTransaction();
    db.setAppUserId(this->id());
    db.executeNonQuery("CALL updateOrderStatus(" + std::to_string(orderId) + ", " + db.quote("completed") + ", " + std::to_string(this->id()) + ");");
    db.commitTransaction();
}

void Manager::updateStock(DatabaseConnection<std::string>& db, int productId, int newStock) {
    try {
        db.beginTransaction();
        db.setAppUserId(this->id());

        db.executeNonQuery(
            "UPDATE products SET stock_quantity=" + std::to_string(newStock) +
            " WHERE product_id=" + std::to_string(productId) + ";"
        );

        db.commitTransaction();
    } catch (const std::exception& e) {
        db.rollbackTransaction();
        db.executeNonQuery(
            "INSERT INTO audit_log(entity_type, entity_id, operation, performed_by, details) VALUES "
            "('product', " + std::to_string(productId) + ", 'error', " + std::to_string(this->id()) + ", " + db.quote(e.what()) + ");"
        );
        throw;
    }
}

std::shared_ptr<Order> Manager::createOrder(DatabaseConnection<std::string>&) {
    auto o = std::make_shared<Order>(-1, this->id());
    attachOrder(o);
    return o;
}
std::string Manager::viewOrderStatus(DatabaseConnection<std::string>& db, int orderId) {
    auto r = db.executeQuery("SELECT getOrderStatus(" + std::to_string(orderId) + ");");
    return r.at(0).at(0);
}
void Manager::cancelOrder(DatabaseConnection<std::string>& db, int orderId) {
    if (!canChangeOrderStatus(*this)) throw std::runtime_error("Access denied");
    db.beginTransaction();
    db.setAppUserId(this->id());
    db.executeNonQuery("CALL updateOrderStatus(" + std::to_string(orderId) + ", " + db.quote("canceled") + ", " + std::to_string(this->id()) + ");");
    db.commitTransaction();
}


void Customer::addToOrder(std::shared_ptr<Order> order, int productId, int qty, double price) {
    if (!order) throw std::runtime_error("Order is null");
    order->addItem(productId, qty, price);
}

void Customer::removeFromOrder(std::shared_ptr<Order> order, int productId) {
    if (!order) throw std::runtime_error("Order is null");
    order->removeItem(productId);
}

void Customer::makePayment(std::shared_ptr<Order> order, std::unique_ptr<PaymentStrategy> strategy) {
    if (!order) throw std::runtime_error("Order is null");
    order->setPaymentStrategy(std::move(strategy));
    order->pay();
}

void Customer::returnProduct(DatabaseConnection<std::string>& db, int orderId) {

    db.beginTransaction();
    db.setAppUserId(this->id());
    db.executeNonQuery("CALL updateOrderStatus(" + std::to_string(orderId) + ", " + db.quote("returned") + ", " + std::to_string(this->id()) + ");");
    db.commitTransaction();
}

std::shared_ptr<Order> Customer::createOrder(DatabaseConnection<std::string>&) {
    auto o = std::make_shared<Order>(-1, this->id());
    attachOrder(o);
    return o;
}
std::string Customer::viewOrderStatus(DatabaseConnection<std::string>& db, int orderId) {
    auto r = db.executeQuery("SELECT getOrderStatus(" + std::to_string(orderId) + ");");
    return r.at(0).at(0);
}
void Customer::cancelOrder(DatabaseConnection<std::string>& db, int orderId) {
    db.beginTransaction();
    db.setAppUserId(this->id());
    db.executeNonQuery("CALL updateOrderStatus(" + std::to_string(orderId) + ", " + db.quote("canceled") + ", " + std::to_string(this->id()) + ");");
    db.commitTransaction();
}

int Customer::checkoutToDatabase(DatabaseConnection<std::string>& db, std::shared_ptr<Order> order) {
    if (!order) throw std::runtime_error("Order is null");
    if (order->items().empty()) throw std::runtime_error("Order has no items");

    std::string json = "[";
    for (size_t i = 0; i < order->items().size(); ++i) {
        const auto& it = order->items()[i];
        if (i) json += ",";
        json += "{\"product_id\":" + std::to_string(it.productId())
             + ",\"quantity\":" + std::to_string(it.quantity()) + "}";
    }
    json += "]";

    try {
        db.beginTransaction();
        db.setAppUserId(this->id());



        db.executeNonQuery(
            "CALL createOrder(" + std::to_string(this->id()) + ", " + db.quote(json) + "::jsonb, NULL);"
        );

        auto r = db.executeQuery(
            "SELECT MAX(order_id) FROM orders WHERE user_id=" + std::to_string(this->id()) + ";"
        );

        db.commitTransaction();

        int newId = std::stoi(r.at(0).at(0));
        order->setId(newId);
        return newId;

    } catch (const std::exception& e) {
        db.rollbackTransaction();
        db.executeNonQuery(
            "INSERT INTO audit_log(entity_type, entity_id, operation, performed_by, details) VALUES "
            "('order', -1, 'error', " + std::to_string(this->id()) + ", " + db.quote(e.what()) + ");"
        );
        throw;
    }
}
