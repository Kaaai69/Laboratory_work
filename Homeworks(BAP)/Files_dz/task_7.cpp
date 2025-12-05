#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <numeric>

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

int main()
{
    std::string line;

    std::string id, name, category, price, quantity;
    int new_id, new_price, new_quantity;
    double max_value = 0;
    double min_value = 607.5;
    Product most_valueble;
    Product min_valueble;
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
            if (new_price > max_value) {
                max_value = new_price;
                most_valueble = {new_id, name, category, static_cast<double>(new_price), new_quantity};
            }
            if (new_price < min_value) {
                min_value = new_price;
                min_valueble = {new_id, name, category, static_cast<double>(new_price), new_quantity};
            }
            Product new_product;
            new_product = {new_id, name, category, static_cast<double>(new_price), new_quantity};
            printData(new_product);
            DataProduct.push_back(new_product);
        }
    }
    else if (inFile.fail()){
        std::cerr << "Не удалось открыть файл!\n";
    }
    inFile.close();
    cout << "\nСамый дорогостоящий товар: \n";
    printData(most_valueble);
    cout << "Самый дешевый товар: \n";
    printData(min_valueble);
    double sum = std::accumulate(DataProduct.begin(), DataProduct.end(), 0.0, [](double acc, const Product& p){return acc + p.price;});
    int sum_quantity = std::accumulate(DataProduct.begin(), DataProduct.end(), 0, [](int acc, const Product& q){return acc + q.quantity;});
    cout << "Общее количество товаров: " << sum_quantity << "\n";
    cout << "Общая цена: " << sum << "\n";
    return 0;
}