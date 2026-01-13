#include "Menu.h"
#include <iostream>
#include <limits>

MenuApp::MenuApp(DatabaseConnection<std::string>& db) : db_(db) {}

int MenuApp::readInt(const std::string& prompt) {
    std::cout << prompt;
    int x;
    while (!(std::cin >> x)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter a number: ";
    }
    return x;
}

std::string MenuApp::readStr(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::cin >> s;
    return s;
}

std::unique_ptr<User> MenuApp::loginAs(int choice) {
    if (choice == 1) return std::make_unique<Admin>(1, "Admin");
    if (choice == 2) return std::make_unique<Manager>(2, "Manager");
    if (choice == 3) return std::make_unique<Customer>(3, "Customer");
    return nullptr;
}

void MenuApp::run() {
    while (true) {
        std::cout << "\nПожалуйста, выберите свою роль:\n"
                  << "1. Войти как Администратор\n"
                  << "2. Войти как Менеджер\n"
                  << "3. Войти как Покупатель\n"
                  << "4. Выход\n";

        int c = readInt("> ");
        if (c == 4) break;

        auto user = loginAs(c);
        if (!user) continue;

        if (user->role() == "admin") adminMenu(*static_cast<Admin*>(user.get()));
        else if (user->role() == "manager") managerMenu(*static_cast<Manager*>(user.get()));
        else customerMenu(*static_cast<Customer*>(user.get()));
    }
}


void MenuApp::adminMenu(Admin& admin) {
    while (true) {
        std::cout << "\nМеню администратора:\n"
                  << "1. Добавить новый продукт\n"
                  << "2. Обновить информацию о продукте\n"
                  << "3. Удалить продукт\n"
                  << "4. Просмотр всех заказов\n"
                  << "5. Изменить статус заказа\n"
                  << "6. Просмотр истории статусов заказа\n"
                  << "7. Просмотр журнала аудита (по пользователю)\n"
                  << "8. Сформировать отчёт (CSV)\n"
                  << "9. Выход\n";

        int c = readInt("> ");
        if (c == 9) break;

        try {
            if (c == 1) {
                Product p;
                p.name = readStr("Название: ");
                p.price = readInt("Цена (целым числом для теста): ");
                p.stock = readInt("Количество: ");
                admin.addProduct(db_, p);
            } else if (c == 2) {
                Product p;
                p.id = readInt("product_id: ");
                p.name = readStr("Название: ");
                p.price = readInt("Цена (целым числом для теста): ");
                p.stock = readInt("Количество: ");
                admin.updateProduct(db_, p);
            } else if (c == 3) {
                int pid = readInt("product_id: ");
                admin.deleteProduct(db_, pid);
            } else if (c == 4) {
                admin.viewAllOrders(db_);
            } else if (c == 5) {
                int oid = readInt("order_id: ");
                std::string st = readStr("new_status (pending/completed/canceled/returned): ");
                admin.updateOrderStatus(db_, oid, st);
            } else if (c == 6) {
                int oid = readInt("order_id: ");
                auto hist = db_.executeQuery("SELECT * FROM getOrderStatusHistory(" + std::to_string(oid) + ");");
                for (auto& r : hist) {
                    std::cout << r[0] << " -> " << r[1] << " at " << r[2] << " by " << r[3] << "\n";
                }
            } else if (c == 7) {
                int uid = readInt("user_id: ");
                auto audit = db_.executeQuery("SELECT * FROM getAuditLogByUser(" + std::to_string(uid) + ") LIMIT 50;");
                for (auto& r : audit) {
                    std::cout << "[" << r[0] << "] id=" << r[1] << " op=" << r[2] << " at " << r[3]
                              << " details=" << r[4] << "\n";
                }
            } else if (c == 8) {
                admin.exportCsvReport(db_, "../reports/audit_report.csv");
                std::cout << "CSV saved to reports/audit_report.csv\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    }
}


void MenuApp::managerMenu(Manager& manager) {

    auto canSeeOrderHistory = [&](int orderId) {
        auto r = db_.executeQuery(
            "SELECT COUNT(*) FROM orders WHERE order_id=" + std::to_string(orderId) +
            " AND approved_by=" + std::to_string(manager.id()) + ";"
        );
        return std::stoi(r[0][0]) > 0;
    };

    while (true) {
        std::cout << "\nМеню менеджера:\n"
                  << "1. Просмотр заказов, утверждённых мной\n"
                  << "2. Утвердить заказ (перевести в completed)\n"
                  << "3. Обновить количество товара на складе\n"
                  << "4. Просмотр истории статусов заказа (только моих)\n"
                  << "5. Просмотр аудита по заказам (только order)\n"
                  << "6. Выход\n";

        int c = readInt("> ");
        if (c == 6) break;

        try {
            if (c == 1) {
                auto rows = db_.executeQuery(
                    "SELECT order_id, user_id, status, total_price FROM orders "
                    "WHERE approved_by=" + std::to_string(manager.id()) + " ORDER BY order_id;"
                );
                for (auto& r : rows) {
                    std::cout << "Order #" << r[0] << " user=" << r[1] << " status=" << r[2] << " total=" << r[3] << "\n";
                }
            } else if (c == 2) {
                int oid = readInt("order_id: ");
                manager.approveOrder(db_, oid);
            } else if (c == 3) {
                int pid = readInt("product_id: ");
                int st = readInt("new stock: ");
                manager.updateStock(db_, pid, st);
            } else if (c == 4) {
                int oid = readInt("order_id: ");
                if (!canSeeOrderHistory(oid)) {
                    std::cout << "Доступ запрещён (не ваш заказ)\n";
                    continue;
                }
                auto hist = db_.executeQuery("SELECT * FROM getOrderStatusHistory(" + std::to_string(oid) + ");");
                for (auto& r : hist) {
                    std::cout << r[0] << " -> " << r[1] << " at " << r[2] << " by " << r[3] << "\n";
                }
            } else if (c == 5) {

                auto audit = db_.executeQuery(
                    "SELECT entity_type, entity_id, operation, performed_by, performed_at, details "
                    "FROM audit_log WHERE entity_type='order' ORDER BY performed_at DESC LIMIT 50;"
                );
                for (auto& r : audit) {
                    std::cout << "[" << r[0] << "] id=" << r[1] << " op=" << r[2]
                              << " by " << r[3] << " at " << r[4] << " details=" << r[5] << "\n";
                }
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    }
}


void MenuApp::customerMenu(Customer& customer) {

    auto canSeeOrderHistory = [&](int orderId) {
        auto r = db_.executeQuery(
            "SELECT COUNT(*) FROM orders WHERE order_id=" + std::to_string(orderId) +
            " AND user_id=" + std::to_string(customer.id()) + ";"
        );
        return std::stoi(r[0][0]) > 0;
    };

    std::shared_ptr<Order> current;

    while (true) {
        std::cout << "\nМеню покупателя:\n"
                  << "1. Создать новый заказ (локально)\n"
                  << "2. Добавить товар в заказ (локально)\n"
                  << "3. Удалить товар из заказа (локально)\n"
                  << "4. Оформить заказ в БД (createOrder)\n"
                  << "5. Просмотр статуса заказа\n"
                  << "6. Оплатить заказ (стратегия)\n"
                  << "7. Оформить возврат заказа\n"
                  << "8. Просмотр истории статусов заказа\n"
                  << "9. Выход\n";

        int c = readInt("> ");
        if (c == 9) break;

        try {
            if (c == 1) {
                current = customer.createOrder(db_);
                std::cout << "Локальный заказ создан.\n";
            } else if (c == 2) {
                if (!current) { std::cout << "Сначала создайте заказ.\n"; continue; }
                int pid = readInt("product_id: ");
                int qty = readInt("quantity: ");
                auto pr = db_.executeQuery("SELECT price FROM products WHERE product_id=" + std::to_string(pid) + ";");
                double price = std::stod(pr.at(0).at(0));
                customer.addToOrder(current, pid, qty, price);
            } else if (c == 3) {
                if (!current) { std::cout << "Сначала создайте заказ.\n"; continue; }
                int pid = readInt("product_id: ");
                customer.removeFromOrder(current, pid);
            } else if (c == 4) {
                if (!current) { std::cout << "Сначала создайте заказ.\n"; continue; }
                int oid = customer.checkoutToDatabase(db_, current);
                std::cout << "Заказ оформлен в БД. order_id=" << oid << "\n";
            } else if (c == 5) {
                int oid = readInt("order_id: ");
                std::cout << "Status: " << customer.viewOrderStatus(db_, oid) << "\n";
            } else if (c == 6) {
                if (!current) { std::cout << "Сначала создайте заказ.\n"; continue; }
                std::cout << "1) Card 2) Wallet 3) SBP\n";
                int m = readInt("> ");
                if (m == 1) customer.makePayment(current, std::make_unique<CardPayment>());
                else if (m == 2) customer.makePayment(current, std::make_unique<WalletPayment>());
                else customer.makePayment(current, std::make_unique<SBPPayment>());
            } else if (c == 7) {
                int oid = readInt("order_id: ");
                customer.returnProduct(db_, oid);
                std::cout << "Return requested.\n";
            } else if (c == 8) {
                int oid = readInt("order_id: ");
                if (!canSeeOrderHistory(oid)) {
                    std::cout << "Доступ запрещён (не ваш заказ)\n";
                    continue;
                }
                auto hist = db_.executeQuery("SELECT * FROM getOrderStatusHistory(" + std::to_string(oid) + ");");
                for (auto& r : hist) {
                    std::cout << r[0] << " -> " << r[1] << " at " << r[2] << " by " << r[3] << "\n";
                }
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
        int oid = readInt("order_id (local): ");
        auto it = std::find_if(customer.orders().begin(), customer.orders().end(),
            [&](const std::shared_ptr<Order>& o){ return o && o->id() == oid; });

        if (it == customer.orders().end()) {
            std::cout << "Не найден локальный заказ.\n";
        } else {
            current = *it;
            std::cout << "Текущий заказ выбран.\n";
        }
    }
}
