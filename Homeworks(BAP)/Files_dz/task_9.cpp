#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <numeric>
#include <algorithm>

using std::cout;

struct Product {
    int id;
    std::string name;
    std::string category;
    double price;
    int quantity;
};

void printData(const Product& product) {
    cout << "id: " << product.id << ", name: " << product.name << ", category: " << product.category << ", price: " << product.price << ", quantity: " << product.quantity << "\n";
}

void sortedByprice(std::vector<Product>& products){
    std::sort(products.begin(), products.end(), [](const Product& a, const Product& b){return a.price < b.price;});
    std::ofstream outFile("sorted_products.txt");
    if (outFile.is_open()){
        for (const auto& p : products){
            outFile << p.id << "," << p.name  << "," << p.category << "," << p.price << "," << p.quantity << "\n";
            printData(p);
        }
    }
    else if (outFile.fail()){
        std::cerr << "Не удалось открыть файл!\n";
    }
    outFile.close();
}

void sortedBypriceRev(std::vector<Product>& products){
    std::sort(products.begin(), products.end(), [](const Product& a, const Product& b){return a.price > b.price;});
    std::ofstream outFile("sorted_products.txt");
    if (outFile.is_open()){
        for (const auto& p : products){
            outFile << p.id << "," << p.name  << "," << p.category << "," << p.price << "," << p.quantity << "\n";
            printData(p);
        }
    }
    else if (outFile.fail()){
        std::cerr << "Не удалось открыть файл!\n";
    }
    outFile.close();
}

void sortedByquantity(std::vector<Product>& products){
    std::sort(products.begin(), products.end(), [](const Product& a, const Product& b){return a.quantity > b.quantity;});
    std::ofstream outFile("sorted_products.txt");
    if (outFile.is_open()){
        for (const auto& p : products){
            outFile << p.id << "," << p.name  << "," << p.category << "," << p.price << "," << p.quantity << "\n";
            printData(p);
        }
    }
    else if (outFile.fail()){
        std::cerr << "Не удалось открыть файл!\n";
    }
    outFile.close();
}

void sortedByname(std::vector<Product>& products){
    std::sort(products.begin(), products.end(), [](const Product& a, const Product& b){return a.name < b.name;});
    std::ofstream outFile("sorted_products.txt");
    if (outFile.is_open()){
        for (const auto& p : products){
            outFile << p.id << "," << p.name  << "," << p.category << "," << p.price << "," << p.quantity << "\n";
            printData(p);
        }
    }
    else if (outFile.fail()){
        std::cerr << "Не удалось открыть файл!\n";
    }
    outFile.close();
}

int main()
{
    std::string line;

    std::string id, name, category, price, quantity;
    int new_id, new_price, new_quantity;
    double max_value = 0;
    double min_value = 607.5;
    std::vector<Product> DataProduct;
    std::ifstream inFile("products.txt");
    if (inFile.is_open()){
        while (std::getline(inFile, line)){
            std::istringstream iss(line, ',');
            std::getline(iss, id, ',');
            std::getline(iss, name, ',');
            std::getline(iss, category, ',');
            std::getline(iss, price, ',');
            std::getline(iss, quantity, ',');
            new_id = std::stoi(id);
            new_price = std::stod(price);
            new_quantity = std::stoi(quantity);

            Product new_product;
            new_product = {new_id, name, category, static_cast<double>(new_price), new_quantity};
            DataProduct.push_back(new_product);
        }
    }
    else if (inFile.fail()){
        std::cerr << "Не удалось открыть файл!\n";
    }
    inFile.close();

    int solve;
    do {
        cout << "- - - Меню - - - \n";
        cout << "0 - Завершить программу.\n";
        cout << "1 - Сортировка по возрастанию цены.\n";
        cout << "2 - Сортировка по убыванию цены.\n";
        cout << "3 - Сортировка по названию.\n";
        cout << "4 - Сортировка по количеству.\n";
        cout << "Выберите операцию: ";
        std::cin >> solve;
        std::cin.ignore();
        switch (solve)
        {
            case 0: {
                cout << "Программа завершена, все операции выполнены успешно.\n";
                break;
            }
            case 1: {
                sortedByprice(DataProduct);
                break;
            }
            case 2: {
                sortedBypriceRev(DataProduct);
                break;
            }
            case 3: {
                sortedByname(DataProduct);
                break;
            }
            case 4: {
                sortedByquantity(DataProduct);
                break;
            }
            default:
                cout << "Не нажимайте ерунду.\n";
                break;
        }

    } while(solve != 0);
    return 0;
}