#pragma once
#include "Users.h"
#include <memory>

class MenuApp {
public:
    MenuApp(DatabaseConnection<std::string>& db);

    void run();

private:
    DatabaseConnection<std::string>& db_;

    std::unique_ptr<User> loginAs(int choice);
    void adminMenu(Admin& admin);
    void managerMenu(Manager& manager);
    void customerMenu(Customer& customer);

    int readInt(const std::string& prompt);
    std::string readStr(const std::string& prompt);
};
