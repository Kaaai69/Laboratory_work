#include <iostream>
#include <queue>
#include <vector>
#include <string>


struct Order {
    std::string customerName;
    std::vector<std::string> items;
};


void addOrder(std::queue<Order>& orderQueue, const Order& newOrder) {
    orderQueue.push(newOrder);
    std::cout << "Заказ от " << newOrder.customerName << " добавлен в очередь.\n";
}


void processOrder(std::queue<Order>& orderQueue) {
    if (orderQueue.empty()) {
        std::cout << "Очередь заказов пуста.\n";
        return;
    }
    
    Order currentOrder = orderQueue.front();
    
    std::cout << "\nОбрабатывается заказ клиента: " << currentOrder.customerName << "\n";
    std::cout << "Товары в заказе:\n";
    
    for (size_t i = 0; i < currentOrder.items.size(); ++i) {
        std::cout << "  " << i + 1 << ". " << currentOrder.items[i] << "\n";
    }
    
    orderQueue.pop();
}

void displayQueueStatus(const std::queue<Order>& orderQueue) {
    std::cout << "\nТекущее состояние очереди: " 
              << orderQueue.size() << " заказ(ов) в ожидании.\n";
}

int main() {
    std::queue<Order> orderQueue;
    
    Order order1 = {"Иван", {"Ноутбук", "Мышка", "Чехол"}};
    Order order2 = {"Петр", {"Смартфон", "Наушники"}};
    Order order3 = {"Анна", {"Книга", "Блокнот", "Ручка", "Карандаш"}};
    
    addOrder(orderQueue, order1);
    addOrder(orderQueue, order2);
    addOrder(orderQueue, order3);
    
    displayQueueStatus(orderQueue);
    
    processOrder(orderQueue);
    processOrder(orderQueue);
    processOrder(orderQueue);
    
    processOrder(orderQueue);
    
    displayQueueStatus(orderQueue);
    
    return 0;
}