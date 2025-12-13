#include "Menu.h"
#include "DatabaseManager.h"
#include "Product.h"
#include "Order.h"
#include "Analytics.h"
#include <iostream>
#include <limits>
#include <memory>
#include <iomanip>



void Menu::displayMainMenu() {
    std::cout << "\n=== Sales Management System ===" << std::endl;
    std::cout << "1. Product Management" << std::endl;
    std::cout << "2. Order Management" << std::endl;
    std::cout << "3. Analytics & Reports" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Enter your choice (1-4): ";
}

void Menu::displayProductMenu() {
    std::cout << "\n=== Product Management ===" << std::endl;
    std::cout << "1. Add New Product" << std::endl;
    std::cout << "2. View All Products" << std::endl;
    std::cout << "3. Delete Product" << std::endl;
    std::cout << "4. Back to Main Menu" << std::endl;
    std::cout << "Enter your choice (1-4): ";
}

void Menu::displayOrderMenu() {
    std::cout << "\n=== Order Management ===" << std::endl;
    std::cout << "1. Create New Order" << std::endl;
    std::cout << "2. View All Orders" << std::endl;
    std::cout << "3. Add Item to Order" << std::endl;
    std::cout << "4. View Order Details" << std::endl;
    std::cout << "5. Delete Order" << std::endl;
    std::cout << "6. Back to Main Menu" << std::endl;
    std::cout << "Enter your choice (1-6): ";
}

void Menu::displayAnalyticsMenu() {
    std::cout << "\n=== Analytics & Reports ===" << std::endl;
    std::cout << "1. Revenue by Product" << std::endl;
    std::cout << "2. Top Selling Products" << std::endl;
    std::cout << "3. Average Order Value" << std::endl;
    std::cout << "4. Order Count by Product" << std::endl;
    std::cout << "5. Export Full Report" << std::endl;
    std::cout << "6. Back to Main Menu" << std::endl;
    std::cout << "Enter your choice (1-6): ";
}

void Menu::handleProductChoice(int choice) {
    switch (choice) {
        case 1: {
            std::string name;
            double price;

            std::cout << "Enter product name: ";
            std::getline(std::cin, name);

            std::cout << "Enter product price: ";
            while (!(std::cin >> price) || price < 0) {
                std::cout << "Invalid price. Please enter a positive number: ";
                clearInputBuffer();
            }
            clearInputBuffer();


            std::cout << "Select product type:" << std::endl;
            std::cout << "1. Physical Product" << std::endl;
            std::cout << "2. Digital Product" << std::endl;
            std::cout << "3. Generic Product" << std::endl;
            std::cout << "Enter choice (1-3): ";

            int typeChoice;
            std::cin >> typeChoice;
            clearInputBuffer();

            if (typeChoice == 1) {
                double weight;
                std::string dimensions;

                std::cout << "Enter weight (kg): ";
                std::cin >> weight;
                clearInputBuffer();

                std::cout << "Enter dimensions (e.g., 10x20x30): ";
                std::getline(std::cin, dimensions);

                PhysicalProduct::createPhysicalProduct(name, price, weight, dimensions);
            } else if (typeChoice == 2) {
                std::string format;
                double size;

                std::cout << "Enter file format: ";
                std::getline(std::cin, format);

                std::cout << "Enter file size (MB): ";
                std::cin >> size;
                clearInputBuffer();

                DigitalProduct::createDigitalProduct(name, price, format, size);
            } else {
                // Создаем обычный продукт
                Product::createProduct(name, price);
            }

            std::cout << "Product added successfully!" << std::endl;
            break;
        }

        case 2: {
            auto products = Product::getAllProducts();

            std::cout << "\n=== All Products ===" << std::endl;
            if (products.empty()) {
                std::cout << "No products found." << std::endl;
            } else {
                for (const auto& product : products) {
                    product->displayInfo();
                }

                for (auto product : products) {
                    delete product;
                }
            }
            break;
        }

        case 3: {
            int productId;

            std::cout << "Enter product ID to delete: ";
            std::cin >> productId;
            clearInputBuffer();

            if (Product::deleteProduct(productId)) {
                std::cout << "Product deleted successfully!" << std::endl;
            } else {
                std::cout << "Failed to delete product. It may not exist or be in use." << std::endl;
            }
            break;
        }

        case 4:
            break;

        default:
            std::cout << "Invalid choice! Please try again." << std::endl;
    }
}

void Menu::handleOrderChoice(int choice) {
    switch (choice) {
        case 1: {
            std::string date;

            std::cout << "Enter order date (YYYY-MM-DD) or press Enter for today: ";
            std::getline(std::cin, date);

            int orderId = Order::createOrder(date);
            if (orderId > 0) {
                std::cout << "Order created successfully! Order ID: " << orderId << std::endl;
            } else {
                std::cout << "Failed to create order." << std::endl;
            }
            break;
        }

        case 2: {
            auto orders = Order::getAllOrders();

            std::cout << "\n=== All Orders ===" << std::endl;
            if (orders.empty()) {
                std::cout << "No orders found." << std::endl;
            } else {
                for (const auto& order : orders) {
                    order.display();
                }
            }
            break;
        }

        case 3: {
            int orderId, productId, quantity;

            std::cout << "Enter order ID: ";
            std::cin >> orderId;

            std::cout << "Enter product ID: ";
            std::cin >> productId;

            std::cout << "Enter quantity: ";
            std::cin >> quantity;
            clearInputBuffer();

            if (OrderItem::addItemToOrder(orderId, productId, quantity)) {
                std::cout << "Item added to order successfully!" << std::endl;
            } else {
                std::cout << "Failed to add item to order." << std::endl;
            }
            break;
        }

        case 4: {
            int orderId;

            std::cout << "Enter order ID: ";
            std::cin >> orderId;
            clearInputBuffer();

            try {
                Order order = Order::getOrderById(orderId);
                order.display();
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        }

        case 5: {
            int orderId;

            std::cout << "Enter order ID to delete: ";
            std::cin >> orderId;
            clearInputBuffer();

            if (Order::deleteOrder(orderId)) {
                std::cout << "Order deleted successfully!" << std::endl;
            } else {
                std::cout << "Failed to delete order." << std::endl;
            }
            break;
        }

        case 6:
            break;

        default:
            std::cout << "Invalid choice! Please try again." << std::endl;
    }
}

void Menu::handleAnalyticsChoice(int choice) {
    switch (choice) {
        case 1: {
            auto revenue = Analytics::getRevenueByProduct();

            std::cout << "\n=== Revenue by Product ===" << std::endl;
            if (revenue.empty()) {
                std::cout << "No revenue data available." << std::endl;
            } else {
                for (const auto& item : revenue) {
                    std::cout << item.getFirst() << ": $"
                              << std::fixed << std::setprecision(2)
                              << item.getSecond() << std::endl;
                }
            }
            break;
        }

        case 2: {
            auto topProducts = Analytics::getTopSellingProducts(3);

            std::cout << "\n=== Top 3 Selling Products ===" << std::endl;
            if (topProducts.empty()) {
                std::cout << "No sales data available." << std::endl;
            } else {
                for (size_t i = 0; i < topProducts.size(); ++i) {
                    std::cout << i + 1 << ". " << topProducts[i].getFirst()
                              << " - Sold: " << topProducts[i].getSecond() << " units" << std::endl;
                }
            }
            break;
        }

        case 3: {
            double avg = Analytics::getAverageOrderValue();
            std::cout << "\n=== Average Order Value ===" << std::endl;
            std::cout << "$" << std::fixed << std::setprecision(2) << avg << std::endl;
            break;
        }

        case 4: {
            auto orderCounts = Analytics::getOrderCountByProduct();

            std::cout << "\n=== Order Count by Product ===" << std::endl;
            if (orderCounts.empty()) {
                std::cout << "No order data available." << std::endl;
            } else {
                for (const auto& item : orderCounts) {
                    std::cout << item.getFirst() << ": "
                              << item.getSecond() << " orders" << std::endl;
                }
            }
            break;
        }

        case 5: {
            if (Analytics::exportReportToFile("sales_report.txt")) {
                std::cout << "Report exported to 'sales_report.txt'" << std::endl;
            } else {
                std::cout << "Failed to export report." << std::endl;
            }
            break;
        }

        case 6:
            break;

        default:
            std::cout << "Invalid choice! Please try again." << std::endl;
    }
}

void Menu::run() {
    int mainChoice;
    bool running = true;

    while (running) {
        displayMainMenu();
        std::cin >> mainChoice;
        clearInputBuffer();

        switch (mainChoice) {
            case 1: {
                int productChoice;
                do {
                    displayProductMenu();
                    std::cin >> productChoice;
                    clearInputBuffer();
                    handleProductChoice(productChoice);
                } while (productChoice != 4);
                break;
            }

            case 2: {
                int orderChoice;
                do {
                    displayOrderMenu();
                    std::cin >> orderChoice;
                    clearInputBuffer();
                    handleOrderChoice(orderChoice);
                } while (orderChoice != 6);
                break;
            }

            case 3: {
                int analyticsChoice;
                do {
                    displayAnalyticsMenu();
                    std::cin >> analyticsChoice;
                    clearInputBuffer();
                    handleAnalyticsChoice(analyticsChoice);
                } while (analyticsChoice != 6);
                break;
            }

            case 4:
                std::cout << "Thank you for using Sales Management System!" << std::endl;
                running = false;
                break;

            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
        }
    }
}