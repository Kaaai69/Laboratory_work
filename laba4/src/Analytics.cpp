#include "Analytics.h"
#include "DatabaseManager.h"
#include <iostream>
#include <iomanip>
#include <fstream>

std::vector<Pair<std::string, double>> Analytics::getRevenueByProduct() {
    std::vector<Pair<std::string, double>> result;
    auto& db = DatabaseManager::getInstance();

    try {
        pqxx::work txn(db.getConnection());

        std::string query =
            "SELECT p.name, SUM(oi.total_price) as revenue "
            "FROM products p "
            "JOIN order_items oi ON p.id = oi.product_id "
            "GROUP BY p.name "
            "ORDER BY revenue DESC";

        pqxx::result res = txn.exec(query);

        for (const auto& row : res) {
            result.push_back(Pair<std::string, double>(
                row["name"].c_str(),
                row["revenue"].as<double>()
            ));
        }

        txn.commit();
        db.logOperation("ANALYTICS", "Executed: getRevenueByProduct");

    } catch (const std::exception& e) {
        db.logOperation("ERROR", std::string("Revenue analysis failed: ") + e.what());
    }

    return result;
}

std::vector<Pair<std::string, int>> Analytics::getTopSellingProducts(int limit) {
    std::vector<Pair<std::string, int>> result;
    auto& db = DatabaseManager::getInstance();

    try {
        pqxx::work txn(db.getConnection());

        std::string query =
            "SELECT p.name, SUM(oi.quantity) as total_quantity "
            "FROM products p "
            "JOIN order_items oi ON p.id = oi.product_id "
            "GROUP BY p.name "
            "ORDER BY total_quantity DESC "
            "LIMIT " + std::to_string(limit);

        pqxx::result res = txn.exec(query);

        for (const auto& row : res) {
            result.push_back(Pair<std::string, int>(
                row["name"].c_str(),
                row["total_quantity"].as<int>()
            ));
        }

        txn.commit();
        db.logOperation("ANALYTICS", "Executed: getTopSellingProducts");

    } catch (const std::exception& e) {
        db.logOperation("ERROR", std::string("Top products analysis failed: ") + e.what());
    }

    return result;
}

double Analytics::getAverageOrderValue() {
    auto& db = DatabaseManager::getInstance();

    try {
        pqxx::work txn(db.getConnection());

        std::string query =
            "SELECT COALESCE(AVG(order_total), 0) as average_value FROM ("
            "SELECT o.order_id, SUM(oi.total_price) as order_total "
            "FROM orders o "
            "JOIN order_items oi ON o.order_id = oi.order_id "
            "GROUP BY o.order_id"
            ") as order_totals";

        pqxx::result res = txn.exec(query);

        if (!res.empty()) {
            double avg = res[0]["average_value"].as<double>();
            txn.commit();
            db.logOperation("ANALYTICS",
                           "Average order value: $" + std::to_string(avg));
            return avg;
        }

    } catch (const std::exception& e) {
        db.logOperation("ERROR", std::string("Average calculation failed: ") + e.what());
    }

    return 0.0;
}

std::vector<Pair<std::string, int>> Analytics::getOrderCountByProduct() {
    std::vector<Pair<std::string, int>> result;
    auto& db = DatabaseManager::getInstance();

    try {
        pqxx::work txn(db.getConnection());

        std::string query =
            "SELECT p.name, COUNT(DISTINCT oi.order_id) as order_count "
            "FROM products p "
            "LEFT JOIN order_items oi ON p.id = oi.product_id "
            "GROUP BY p.name "
            "ORDER BY order_count DESC, p.name";

        pqxx::result res = txn.exec(query);

        for (const auto& row : res) {
            result.push_back(Pair<std::string, int>(
                row["name"].c_str(),
                row["order_count"].as<int>()
            ));
        }

        txn.commit();
        db.logOperation("ANALYTICS", "Executed: getOrderCountByProduct");

    } catch (const std::exception& e) {
        db.logOperation("ERROR", std::string("Order count analysis failed: ") + e.what());
    }

    return result;
}

double Analytics::getTotalRevenue() {
    auto& db = DatabaseManager::getInstance();

    try {
        pqxx::work txn(db.getConnection());

        std::string query = "SELECT COALESCE(SUM(total_price), 0) as total FROM order_items";
        pqxx::result res = txn.exec(query);

        if (!res.empty()) {
            double total = res[0]["total"].as<double>();
            txn.commit();
            return total;
        }

    } catch (const std::exception& e) {
        db.logOperation("ERROR", std::string("Total revenue calculation failed: ") + e.what());
    }

    return 0.0;
}

std::vector<Pair<std::string, double>> Analytics::getDailyRevenue(
    const std::string& startDate, const std::string& endDate) {

    std::vector<Pair<std::string, double>> result;
    auto& db = DatabaseManager::getInstance();

    try {
        pqxx::work txn(db.getConnection());

        std::string query =
            "SELECT o.order_date, SUM(oi.total_price) as daily_revenue "
            "FROM orders o "
            "JOIN order_items oi ON o.order_id = oi.order_id "
            "WHERE o.order_date BETWEEN " + txn.quote(startDate) +
            " AND " + txn.quote(endDate) +
            " GROUP BY o.order_date "
            "ORDER BY o.order_date";

        pqxx::result res = txn.exec(query);

        for (const auto& row : res) {
            result.push_back(Pair<std::string, double>(
                row["order_date"].c_str(),
                row["daily_revenue"].as<double>()
            ));
        }

        txn.commit();
        db.logOperation("ANALYTICS",
                       "Executed: getDailyRevenue from " + startDate + " to " + endDate);

    } catch (const std::exception& e) {
        db.logOperation("ERROR", std::string("Daily revenue analysis failed: ") + e.what());
    }

    return result;
}

bool Analytics::exportReportToFile(const std::string& filename) {
    std::ofstream reportFile(filename);
    if (!reportFile.is_open()) {
        return false;
    }

    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    reportFile << "=== Sales Analytics Report ===" << std::endl;
    reportFile << "Generated: " << ctime(&time) << std::endl;

    // 1. Выручка по товарам
    reportFile << "\n1. Revenue by Product:" << std::endl;
    reportFile << std::setw(30) << std::left << "Product Name"
               << std::setw(15) << std::right << "Revenue" << std::endl;
    reportFile << std::string(45, '-') << std::endl;

    auto revenue = getRevenueByProduct();
    for (const auto& item : revenue) {
        reportFile << std::setw(30) << std::left << item.getFirst()
                   << std::setw(15) << std::right << std::fixed << std::setprecision(2)
                   << "$" << item.getSecond() << std::endl;
    }

    // 2. Топ товаров
    reportFile << "\n2. Top Selling Products:" << std::endl;
    auto topProducts = getTopSellingProducts(5);
    for (size_t i = 0; i < topProducts.size(); ++i) {
        reportFile << i + 1 << ". " << topProducts[i].getFirst()
                   << " - Sold: " << topProducts[i].getSecond() << " units" << std::endl;
    }

    // 3. Общая статистика
    reportFile << "\n3. Overall Statistics:" << std::endl;
    reportFile << "Total Revenue: $" << std::fixed << std::setprecision(2)
               << getTotalRevenue() << std::endl;
    reportFile << "Average Order Value: $" << std::fixed << std::setprecision(2)
               << getAverageOrderValue() << std::endl;

    reportFile.close();

    DatabaseManager::getInstance().logOperation("EXPORT",
                                               "Report exported to " + filename);
    return true;
}