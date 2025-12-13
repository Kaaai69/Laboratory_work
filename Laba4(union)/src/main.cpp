#include "DatabaseManager.h"
#include "Menu.h"
#include <iostream>

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "     Sales Management System v1.0" << std::endl;
    std::cout << "     MGTU Bauman - Lab Work #4" << std::endl;
    std::cout << "========================================" << std::endl;


    auto& db = DatabaseManager::getInstance();


    std::string connStr = "host=localhost port=5432 dbname=sales_db user=postgres password=MyNewStrongPass123";

    if (!db.connect(connStr)) {
        std::cerr << "\nERROR: Failed to connect to database!" << std::endl;
        std::cerr << "Please ensure:" << std::endl;
        std::cerr << "1. PostgreSQL server is running" << std::endl;
        std::cerr << "2. Database 'sales_db' exists" << std::endl;
        std::cerr << "3. Connection string is correct" << std::endl;
        return 1;
    }


    std::cout << "\nInitializing database..." << std::endl;
    if (!db.initializeDatabase()) {
        std::cerr << "WARNING: Database initialization completed with errors." << std::endl;
        std::cerr << "Some features may not work correctly." << std::endl;
    } else {
        std::cout << "Database initialized successfully!" << std::endl;
    }

    // Запускаем меню
    Menu menu;
    menu.run();

    std::cout << "\nProgram terminated. Goodbye!" << std::endl;
    return 0;
}