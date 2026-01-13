#include "DatabaseConnection.h"
#include "Menu.h"
#include <iostream>

int main() {
    try {
        const std::string connStr =
            "host=localhost port=5432 dbname=online_store user=postgres password=MyNewStrongPass123";
        DatabaseConnection<std::string> db(connStr);

        MenuApp app(db);
        app.run();

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Fatal: " << e.what() << "\n";
        return 1;
    }
}