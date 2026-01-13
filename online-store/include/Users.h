#pragma once
#include "Models.h"
#include "DatabaseConnection.h"
#include <vector>
#include <memory>

class User {
public:
    User(int id, std::string name) : id_(id), name_(std::move(name)) {}
    virtual ~User() = default;


    virtual std::string role() const = 0;


    virtual std::shared_ptr<Order> createOrder(DatabaseConnection<std::string>& db) = 0;
    virtual std::string viewOrderStatus(DatabaseConnection<std::string>& db, int orderId) = 0;
    virtual void cancelOrder(DatabaseConnection<std::string>& db, int orderId) = 0;

    int id() const { return id_; }


    const std::vector<std::shared_ptr<Order>>& orders() const { return orders_; }
    void attachOrder(std::shared_ptr<Order> o) { orders_.push_back(std::move(o)); }

protected:
    int id_;
    std::string name_;
    std::vector<std::shared_ptr<Order>> orders_;
};

class Admin : public User {
public:
    using User::User;
    std::string role() const override { return "admin"; }


    void addProduct(DatabaseConnection<std::string>& db, const Product& p);
    void updateProduct(DatabaseConnection<std::string>& db, const Product& p);
    void deleteProduct(DatabaseConnection<std::string>& db, int productId);

    void viewAllOrders(DatabaseConnection<std::string>& db);
    void updateOrderStatus(DatabaseConnection<std::string>& db, int orderId, const std::string& newStatus);


    std::shared_ptr<Order> createOrder(DatabaseConnection<std::string>& db) override;
    std::string viewOrderStatus(DatabaseConnection<std::string>& db, int orderId) override;
    void cancelOrder(DatabaseConnection<std::string>& db, int orderId) override;

    void exportCsvReport(DatabaseConnection<std::string>& db, const std::string& path);
};

class Manager : public User {
public:
    using User::User;
    std::string role() const override { return "manager"; }

    void approveOrder(DatabaseConnection<std::string>& db, int orderId);
    void updateStock(DatabaseConnection<std::string>& db, int productId, int newStock);

    std::shared_ptr<Order> createOrder(DatabaseConnection<std::string>& db) override;
    std::string viewOrderStatus(DatabaseConnection<std::string>& db, int orderId) override;
    void cancelOrder(DatabaseConnection<std::string>& db, int orderId) override;
};

class Customer : public User {
public:
    using User::User;
    std::string role() const override { return "customer"; }

    void addToOrder(std::shared_ptr<Order> order, int productId, int qty, double price);
    void removeFromOrder(std::shared_ptr<Order> order, int productId);
    void makePayment(std::shared_ptr<Order> order, std::unique_ptr<PaymentStrategy> strategy);
    void returnProduct(DatabaseConnection<std::string>& db, int orderId);

    std::shared_ptr<Order> createOrder(DatabaseConnection<std::string>& db) override;
    std::string viewOrderStatus(DatabaseConnection<std::string>& db, int orderId) override;
    void cancelOrder(DatabaseConnection<std::string>& db, int orderId) override;
    int checkoutToDatabase(DatabaseConnection<std::string>& db, std::shared_ptr<Order> order);

};
