#include "Product.h"
#include "DatabaseManager.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <random>
#include <sstream>



Product::Product(int id, const std::string& name, double price, const std::string& type)
    : id(id), name(name), price(price), type(type) {
    if (price < 0) {
        throw std::invalid_argument("Price cannot be negative");
    }
}

void Product::displayInfo() const {
    std::cout << "ID: " << id
              << " | Name: " << name
              << " | Price: $" << std::fixed << std::setprecision(2) << price
              << " | Type: " << getType() << std::endl;
}

bool Product::createProduct(const std::string& name, double price, const std::string& type) {
    auto& db = DatabaseManager::getInstance();

    try {
        pqxx::work txn(db.getConnection());

        std::string query = "INSERT INTO products (name, price, product_type) VALUES (" +
                           txn.quote(name) + ", " +
                           txn.quote(price) + ", " +
                           txn.quote(type) + ") RETURNING id";

        pqxx::result res = txn.exec(query);
        txn.commit();

        int newId = res[0]["id"].as<int>();
        db.logOperation("CREATE_PRODUCT",
                       "Created product: " + name + " (ID: " + std::to_string(newId) +
                       ", Type: " + type + ")");
        return true;

    } catch (const std::exception& e) {
        db.logOperation("ERROR", std::string("Create product failed: ") + e.what());
        return false;
    }
}

Product* Product::getProductById(int productId) {
    auto& db = DatabaseManager::getInstance();

    try {
        pqxx::work txn(db.getConnection());

        std::string query = "SELECT id, name, price, product_type FROM products WHERE id = " +
                           txn.quote(productId);

        pqxx::result res = txn.exec(query);

        if (res.empty()) {
            return nullptr;
        }

        auto row = res[0];
        int id = row["id"].as<int>();
        std::string name = row["name"].c_str();
        double price = row["price"].as<double>();
        std::string type = row["product_type"].c_str();

        if (type == "physical") {
            return new PhysicalProduct(id, name, price, 1.0, "10x10x10 cm");
        } else if (type == "digital") {
            return new DigitalProduct(id, name, price, "PDF", 5.0, "");
        } else {
            return new Product(id, name, price, type);
        }

    } catch (const std::exception& e) {
        db.logOperation("ERROR", std::string("Get product failed: ") + e.what());
        return nullptr;
    }
}

bool Product::deleteProduct(int productId) {
    auto& db = DatabaseManager::getInstance();

    try {
        pqxx::work txn(db.getConnection());

        pqxx::result check = txn.exec(
            "SELECT 1 FROM order_items WHERE product_id = " + txn.quote(productId) + " LIMIT 1"
        );

        if (!check.empty()) {
            db.logOperation("WARNING", "Cannot delete product " + std::to_string(productId) +
                           " - it exists in orders");
            return false;
        }

        txn.exec("DELETE FROM products WHERE id = " + txn.quote(productId));
        txn.commit();

        db.logOperation("DELETE_PRODUCT", "Deleted product ID: " + std::to_string(productId));
        return true;

    } catch (const std::exception& e) {
        db.logOperation("ERROR", std::string("Delete product failed: ") + e.what());
        return false;
    }
}

std::vector<Product*> Product::getAllProducts() {
    std::vector<Product*> products;
    auto& db = DatabaseManager::getInstance();

    try {
        pqxx::work txn(db.getConnection());

        std::string query = "SELECT id, name, price, product_type FROM products ORDER BY id";
        pqxx::result res = txn.exec(query);

        for (const auto& row : res) {
            int id = row["id"].as<int>();
            std::string name = row["name"].c_str();
            double price = row["price"].as<double>();
            std::string type = row["product_type"].c_str();

            if (type == "physical") {
                products.push_back(new PhysicalProduct(id, name, price, 1.0, "10x10x10 cm"));
            } else if (type == "digital") {
                products.push_back(new DigitalProduct(id, name, price, "PDF", 5.0, ""));
            } else {
                products.push_back(new Product(id, name, price, type));
            }
        }

        db.logOperation("READ", "Retrieved " + std::to_string(products.size()) + " products");

    } catch (const std::exception& e) {
        db.logOperation("ERROR", std::string("Get all products failed: ") + e.what());
    }

    return products;
}


PhysicalProduct::PhysicalProduct(int id, const std::string& name, double price,
                               double weight, const std::string& dimensions)
    : Product(id, name, price, "Physical"), weight(weight), dimensions(dimensions) {
    if (weight <= 0) {
        throw std::invalid_argument("Weight must be positive");
    }
}

void PhysicalProduct::displayInfo() const {
    Product::displayInfo();
    std::cout << "   Weight: " << weight << " kg | Dimensions: " << dimensions
              << " | Tax: $" << calculateTax() << std::endl;
}

bool PhysicalProduct::createPhysicalProduct(const std::string& name, double price,
                                          double weight, const std::string& dimensions) {

    bool success = Product::createProduct(name, price, "physical");
    if (success) {
        DatabaseManager::getInstance().logOperation("CREATE_PHYSICAL_PRODUCT",
                                                   name + " (Weight: " + std::to_string(weight) +
                                                   "kg, Dimensions: " + dimensions + ")");
    }
    return success;
}



DigitalProduct::DigitalProduct(int id, const std::string& name, double price,
                             const std::string& format, double size, const std::string& license)
    : Product(id, name, price, "Digital"), fileFormat(format), fileSize(size), licenseKey(license) {
    if (fileSize <= 0) {
        throw std::invalid_argument("File size must be positive");
    }
    if (licenseKey.empty()) {
        generateLicenseKey();
    }
}

void DigitalProduct::displayInfo() const {
    Product::displayInfo();
    std::cout << "   Format: " << fileFormat << " | Size: " << fileSize
              << " MB | License: " << licenseKey
              << " | Tax: $" << calculateTax() << std::endl;
}

void DigitalProduct::generateLicenseKey() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);

    std::stringstream ss;
    ss << std::hex;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            ss << dis(gen);
        }
        if (i < 3) ss << "-";
    }

    licenseKey = ss.str();
}

bool DigitalProduct::createDigitalProduct(const std::string& name, double price,
                                        const std::string& format, double size) {
    bool success = Product::createProduct(name, price, "digital");
    if (success) {
        DatabaseManager::getInstance().logOperation("CREATE_DIGITAL_PRODUCT",
                                                   name + " (Format: " + format +
                                                   ", Size: " + std::to_string(size) + "MB)");
    }
    return success;
}