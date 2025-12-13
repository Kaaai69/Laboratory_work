#include "DatabaseManager.h"
#include <iostream>
#include <chrono>
#include <ctime>



DatabaseManager::DatabaseManager() {
    logFile.open("log.txt", std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Warning: Cannot open log file!" << std::endl;
    }
    logOperation("SYSTEM", "Database manager initialized");
}

DatabaseManager::~DatabaseManager() {
    if (conn && conn->is_open()) {
        conn->close();
    }
    logOperation("SYSTEM", "Database manager shutdown");
    if (logFile.is_open()) {
        logFile.close();
    }
}

DatabaseManager& DatabaseManager::getInstance() {
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::connect(const std::string& connStr) {
    try {
        conn = std::make_unique<pqxx::connection>(connStr);
        if (conn->is_open()) {
            logOperation("CONNECT", "Successfully connected to database");
            return true;
        }
    } catch (const std::exception& e) {
        logOperation("ERROR", std::string("Connection failed: ") + e.what());
        std::cerr << "Connection error: " << e.what() << std::endl;
    }
    return false;
}

bool DatabaseManager::initializeDatabase() {
    try {
        pqxx::work txn(getConnection());


        txn.exec(
            "CREATE TABLE IF NOT EXISTS products ("
            "    id SERIAL PRIMARY KEY,"
            "    name VARCHAR(255) NOT NULL,"
            "    price DECIMAL(10, 2) NOT NULL CHECK (price >= 0),"
            "    product_type VARCHAR(50) DEFAULT 'physical'"
            ");"
        );


        txn.exec(
            "CREATE TABLE IF NOT EXISTS orders ("
            "    order_id SERIAL PRIMARY KEY,"
            "    order_date DATE NOT NULL DEFAULT CURRENT_DATE"
            ");"
        );


        txn.exec(
            "CREATE TABLE IF NOT EXISTS order_items ("
            "    order_item_id SERIAL PRIMARY KEY,"
            "    order_id INTEGER NOT NULL REFERENCES orders(order_id) ON DELETE CASCADE,"
            "    product_id INTEGER NOT NULL REFERENCES products(id) ON DELETE CASCADE,"
            "    quantity INTEGER NOT NULL CHECK (quantity > 0),"
            "    total_price DECIMAL(10, 2) NOT NULL CHECK (total_price >= 0),"
            "    UNIQUE(order_id, product_id)"
            ");"
        );

        txn.exec("CREATE INDEX IF NOT EXISTS idx_orders_date ON orders(order_date);");
        txn.exec("CREATE INDEX IF NOT EXISTS idx_order_items_product ON order_items(product_id);");

        txn.commit();
        logOperation("INIT", "Database schema created successfully");
        return true;

    } catch (const std::exception& e) {
        logOperation("ERROR", std::string("Initialization failed: ") + e.what());
        std::cerr << "Initialization error: " << e.what() << std::endl;
        return false;
    }
}

pqxx::connection& DatabaseManager::getConnection() {
    if (!conn || !conn->is_open()) {
        throw std::runtime_error("Database connection is not established");
    }
    return *conn;
}

void DatabaseManager::logOperation(const std::string& operation, const std::string& details) {
    if (logFile.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);

        char timeStr[26];
        ctime_r(&time, timeStr);
        timeStr[24] = '\0';

        logFile << timeStr << " [" << operation << "] " << details << std::endl;
    }
    std::cout << "[" << operation << "] " << details << std::endl;
}