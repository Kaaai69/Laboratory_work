#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using std::cout;

struct Product {
    std::string name_product;
    int amount_of_product;
    int price_product;
};



void adding_product(const Product& product)
{
    std::ofstream outFile("orders.txt", std::ios::app);
    if (outFile.is_open()){
        outFile << product.name_product + "," << product.amount_of_product << "," << product.price_product << ".\n";
        cout << "Информация о товаре успешно добавлена в файл 'orders.txt'(данные перезаписаны)!\n";
    }
    else {
        cout << "Ошибка при открытии файла для записи.\n";
    }
    outFile.close();
}

void adding_product_end(const Product& product)
{
    std::ofstream outFile("orders.txt", std::ios::app);
    if (outFile.is_open()){
        outFile << product.name_product + "," << product.amount_of_product << "," << product.price_product << ".\n";
        cout << "Информация о товаре успешно добавлена в конец файла 'orders.txt'!\n";
    }
    else {
        cout << "Ошибка при открытии файла для записи.\n";
    }
    outFile.close();
}


void search_by_item_number(std::string& name_of)
{
    std::ifstream inFile("orders.txt");
    std::string line, name;
    size_t position;
    int success = 0;
    if (inFile.is_open()){
        while (std::getline(inFile, line)) {
            position = line.find(','); 
            name = line.substr(0, position);
            if (name_of == name) {
                std::ofstream outFile("output.txt");
                if (outFile.is_open()){
                outFile << line << "\n";
                }
                else {
                    cout << "Ошибка при открытии файла для записи.\n";
                }
                success = 1;
                cout << "Найдена информация о товаре: " << line + "\n";
            }
        }
        if (success == 0){
            cout << "Такого товара нет, идите в жопу.\n";
        }
    }
    else {
        cout << "Ошибка при открытии файла для чтения.\n";
    }
    inFile.close();

}


void sorting_by_quantity()
{
    std::ifstream inFile("orders.txt");
    int count_of_line = 0;
    std::string line, needed_line, needed_line_2;
    std::string value_of_amount[50];
    if (inFile.is_open()){
        while (std::getline(inFile, line)){
            value_of_amount[count_of_line] = line;
            count_of_line++;
        }
        inFile.close();
        for(int i = 0; i < count_of_line; i++){
            for(int j = 0; j < count_of_line - i - 1; j++){
                size_t first_cur = value_of_amount[j].find(',');
                size_t second_cur = value_of_amount[j].find(',', first_cur + 1);
                needed_line = value_of_amount[j].substr(first_cur + 1, second_cur - first_cur - 1);
                size_t first_past = value_of_amount[j + 1].find(',');
                size_t second_past = value_of_amount[j + 1].find(',', first_past + 1);
                needed_line_2 = value_of_amount[j + 1].substr(first_past + 1, second_past - first_past - 1);
                int value_cur = std::stoi(needed_line);
                int value_past = std::stoi(needed_line_2);
                if (value_cur > value_past) {
                    std::swap(value_of_amount[j], value_of_amount[j + 1]);
                }
            }
        }
        std::ofstream outFile("orders.txt");
        if (outFile.is_open()){
            for(int i = 0; i < count_of_line; i++){
                outFile << value_of_amount[i] << "\n";
            }
            outFile.close();
        }
        else {
            cout << "Ошибка при открытии файла для записи.\n";
        }
        std::ofstream outFile_1("output.txt");
        if (outFile_1.is_open()){
            for(int i = 0; i < count_of_line; i++){
                outFile_1 << value_of_amount[i] << "\n";
            }
            outFile_1.close();
        }
        else {
            cout << "Ошибка при открытии файла для записи.\n";
        }
        cout << "Сортировка по количеству товара прошла успешно.\n";
    }
    else {
        cout << "Ошибка при открытии файла для чтения.\n";
    }

}


void sorting_by_price()
{
    std::ifstream inFile("orders.txt");
    int count_of_line = 0;
    std::string line, needed_line, needed_line_2;
    std::string value_of_amount[50];
    if (inFile.is_open()){
        while (std::getline(inFile, line)){
            value_of_amount[count_of_line] = line;
            count_of_line++;
        }
        inFile.close();
        for(int i = 0; i < count_of_line; i++){
            for(int j = 0; j < count_of_line - i - 1; j++){
                size_t first_cur = value_of_amount[j].find(',');
                size_t second_cur = value_of_amount[j].find(',', first_cur + 1);
                size_t third_cur = value_of_amount[j].find('.');
                needed_line = value_of_amount[j].substr(second_cur + 1, third_cur - second_cur - 1);
                size_t first_past = value_of_amount[j + 1].find(',');
                size_t second_past = value_of_amount[j + 1].find(',', first_past + 1);
                size_t third_past = value_of_amount[j + 1].find('.');
                needed_line_2 = value_of_amount[j + 1].substr(second_past + 1, third_past - second_past - 1);
                int value_cur = std::stoi(needed_line);
                int value_past = std::stoi(needed_line_2);
                if (value_cur > value_past) {
                    std::swap(value_of_amount[j], value_of_amount[j + 1]);
                }
            }
        }
        std::ofstream outFile_1("orders.txt");
        if (outFile_1.is_open()){
            for(int i = 0; i < count_of_line; i++){
                outFile_1 << value_of_amount[i] << "\n";
            }
            outFile_1.close();
        }
        else {
            cout << "Ошибка при открытии файла для записи.\n";
        }
        std::ofstream outFile("output.txt");
        if (outFile.is_open()){
            for(int i = 0; i < count_of_line; i++){
                outFile << value_of_amount[i] << "\n";
            }
            outFile.close();
        }
        else {
            cout << "Ошибка при открытии файла для записи.\n";
        }
        cout << "Сортировка по цене товара прошла успешно.\n";
    }
    else {
        cout << "Ошибка при открытии файла для чтения.\n";
    }

}

void request_from_the_user (int price_price)
{
    std::ifstream inFile("orders.txt");
    std::string line, needed_line;
    std::vector<std::string> value; 
    if (inFile.is_open()){
        while (std::getline(inFile, line)){
            size_t first_past = line.find(',');
            size_t second_past = line.find(',', first_past + 1);
            size_t third_past = line.find('.');
            needed_line = line.substr(second_past + 1, third_past - second_past - 1);
            int need = std::stoi(needed_line);
            if (need < price_price){
                cout << line + "\n";
                value.push_back(line);
            }
        }
        std::ofstream outFile("output.txt");
        if (outFile.is_open()){
            for (std::string str : value) {
                outFile << str << "\n";
            }
        }
        else {
            cout << "Ошибка при открытии файла для записи.\n";
        }
    }
    else {
        cout << "Ошибка при открытии файла для чтения.\n";
    }
    inFile.close();

}

int main()
{
    int solve;
    do {
        cout << "- - - Меню - - - \n";
        cout << "1 - Создать и заполнить файл данными.\n";
        cout << "2 - Отсортировать файл по количеству товара.\n";
        cout << "3 - Отсортировать файл по цене товара.\n";
        cout << "4 - Добавить данные в конец файла(объединил с первым заданием, работают идентично).\n";
        cout << "5 - Найти товар по названию.\n";
        cout << "6 - Найти товары, стоящие меньше определенного значения.\n";
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
                do {
                    std::string name_product;
                    int amount_of_product, price_product;
                    cout << "Введите название товара: ";
                    std::getline(std::cin, name_product);
                    if (name_product.empty()){
                        break;
                    }
                    cout << "Введите количество единиц товара: ";
                    std::cin >> amount_of_product;
                    cout << "Введите цену за единицу товара: ";
                    std::cin >> price_product;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    Product new_product = {name_product, amount_of_product, price_product};
                    adding_product(new_product);
                } while(true);
                break;
            }
            case 2: {
                sorting_by_quantity();
                break;
            }
            case 3: {
                sorting_by_price();
                break;
            }
            case 4: {
                std::string name_product;
                int amount_of_product, price_product;
                cout << "Введите название товара: ";
                    std::getline(std::cin, name_product);
                    if (name_product.empty()){
                        break;
                    }
                cout << "Введите количество единиц товара: ";
                std::cin >> amount_of_product;
                cout << "Введите цену за единицу товара: ";
                std::cin >> price_product;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Product new_product = {name_product, amount_of_product, price_product};
                adding_product(new_product);
                break;
            }
            case 5: {
                std::string desire_product;
                cout << "Введите название товара, который хотите найти: ";
                std::getline(std::cin, desire_product);
                search_by_item_number(desire_product);
                break;
            }
            case 6: {
                cout << "Введите цену, чтобы увидеть более дешевые товары: ";
                int price;
                std::cin >> price;
                request_from_the_user(price);
                break; 
            }
            default:
                cout << "Не нажимайте ерунду.\n";
                break;
        }

    } while(solve != 0);
    return 0;
}