#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <memory>
#include "Product.h"

class OrderItem {
private:
    int itemId;
    int orderId;
    int productId;
    int quantity;
    double totalPrice;

public:
    OrderItem(int itemId, int orderId, int productId, int quantity, double totalPrice);


    int getItemId() const { return itemId; }
    int getOrderId() const { return orderId; }
    int getProductId() const { return productId; }
    int getQuantity() const { return quantity; }
    double getTotalPrice() const { return totalPrice; }


    static bool addItemToOrder(int orderId, int productId, int quantity);
    static std::vector<OrderItem> getItemsByOrder(int orderId);
    static bool removeItemFromOrder(int itemId);

    void display() const;
};

class Order {
private:
    int orderId;
    std::string orderDate;
    std::vector<OrderItem> items;

public:
    Order(int orderId, const std::string& date);

    int getOrderId() const { return orderId; }
    std::string getOrderDate() const { return orderDate; }


    void addItem(const OrderItem& item) { items.push_back(item); }
    const std::vector<OrderItem>& getItems() const { return items; }


    static int createOrder(const std::string& date = "");
    static Order getOrderById(int orderId);
    static std::vector<Order> getAllOrders();
    static bool deleteOrder(int orderId);


    double calculateTotal() const;

    void display() const;
};

#endif