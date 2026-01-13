#pragma once
#include <string>
#include <vector>
#include <memory>
#include <numeric>
#include <algorithm>
#include <stdexcept>
#include <iostream>

enum class OrderStatus { Pending, Completed, Canceled, Returned };

inline std::string to_string(OrderStatus s) {
    switch (s) {
        case OrderStatus::Pending: return "pending";
        case OrderStatus::Completed: return "completed";
        case OrderStatus::Canceled: return "canceled";
        case OrderStatus::Returned: return "returned";
    }
    return "pending";
}

struct Product {
    int id{};
    std::string name;
    double price{};
    int stock{};
};


class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual bool pay(double amount) = 0;
};

class CardPayment : public PaymentStrategy {
public:
    bool pay(double amount) override {
        std::cout << "[Card] Paid " << amount << "\n";
        return true;
    }
};

class WalletPayment : public PaymentStrategy {
public:
    bool pay(double amount) override {
        std::cout << "[Wallet] Paid " << amount << "\n";
        return true;
    }
};

class SBPPayment : public PaymentStrategy {
public:
    bool pay(double amount) override {
        std::cout << "[SBP] Paid " << amount << "\n";
        return true;
    }
};

class Payment {
public:
    explicit Payment(std::unique_ptr<PaymentStrategy> strategy)
        : strategy_(std::move(strategy)) {}

    bool process(double amount) {
        if (!strategy_) throw std::runtime_error("Payment strategy not set");
        return strategy_->pay(amount);
    }

private:
    std::unique_ptr<PaymentStrategy> strategy_;
};


class OrderItem {
public:
    OrderItem(int productId, int qty, double price)
        : productId_(productId), quantity_(qty), price_(price) {
        if (qty <= 0) throw std::runtime_error("OrderItem quantity must be > 0");
        if (price <= 0) throw std::runtime_error("OrderItem price must be > 0");
    }

    int productId() const { return productId_; }
    int quantity() const { return quantity_; }
    double price() const { return price_; }

private:
    int productId_;
    int quantity_;
    double price_;
};

class Order {
public:
    Order(int orderId, int userId)
        : orderId_(orderId), userId_(userId) {}

    int id() const { return orderId_; }
    int userId() const { return userId_; }

    void setStatus(OrderStatus s) { status_ = s; }
    OrderStatus status() const { return status_; }


    void addItem(int productId, int qty, double price) {
        items_.emplace_back(productId, qty, price);
    }

    void removeItem(int productId) {
        items_.erase(std::remove_if(items_.begin(), items_.end(),
                    [&](const OrderItem& it){ return it.productId() == productId; }),
                items_.end());
    }

    double total() const {
        return std::accumulate(items_.begin(), items_.end(), 0.0,
            [](double acc, const OrderItem& it){
                return acc + it.price() * it.quantity();
            });
    }


    void setPaymentStrategy(std::unique_ptr<PaymentStrategy> strategy) {
        payment_ = std::make_unique<Payment>(std::move(strategy));
    }

    bool pay() {
        if (!payment_) throw std::runtime_error("Payment is not initialized");
        return payment_->process(total());
    }
    void setId(int newId) { orderId_ = newId; }
    const std::vector<OrderItem>& items() const { return items_; }

private:
    int orderId_;
    int userId_;
    OrderStatus status_{OrderStatus::Pending};

    std::vector<OrderItem> items_;
    std::unique_ptr<Payment> payment_;
};
