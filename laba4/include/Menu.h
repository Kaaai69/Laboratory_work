#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <limits>

class Menu {
private:
    void clearInputBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

public:
    void displayMainMenu();
    void displayProductMenu();
    void displayOrderMenu();
    void displayAnalyticsMenu();


    void handleProductChoice(int choice);
    void handleOrderChoice(int choice);
    void handleAnalyticsChoice(int choice);

    void run();
};

#endif