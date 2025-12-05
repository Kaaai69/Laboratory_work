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
    std::vector<Product> filteredData1(DataProduct.begin(), DataProduct.end());
    std::vector<Product> filteredData2(DataProduct.begin(), DataProduct.end());
    std::vector<Product> filteredData3(DataProduct.begin(), DataProduct.end());
    filteredData1.erase(std::remove_if(filteredData1.begin(), filteredData1.end(), [](const Product& p){return p.price < 2.0 || p.category != "Dairy" || p.quantity <= 20;}), filteredData1.end());

    std::ofstream outFile("sorted_products.txt");
    if (outFile.is_open()){
        for (const auto& p : filteredData1){
            outFile << p.id << "," << p.name  << "," << p.category << "," << p.price << "," << p.quantity << "\n";
            printData(p);
        }
    }
    else if (outFile.fail()){
        std::cerr << "Не удалось открыть файл!\n";
    }
    return 0;
}