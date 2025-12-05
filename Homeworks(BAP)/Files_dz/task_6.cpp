#include <iostream>
#include <random>  // для генераторов и распределений
#include <fstream>
#include <vector>
#include <sstream>

using namespace::std;
int main()
{   
    std::random_device rd;  // случайное зерно
    std::mt19937 gen(rd()); // генератор Mersenne Twister

    // Определение распределения (например, целые числа от 1 до 10)
    std::uniform_int_distribution<> distrib(1, 10000);

    // Генерация случайного числа
    int dice_roll = distrib(gen);
    std::ofstream outFile("products.txt");
    if (outFile.is_open()){
        outFile << "id,name,category,price,quantity\n";
        outFile << "1,Apple,Fruits,1.99,100" << endl;
        outFile << "2,Banana,Fruits,0.99,150" << endl;
        outFile << "3,Milk,Dairy,2.49,50" << endl;
        outFile << "4,Bread,Bakery,1.79,75" << endl;
        outFile << "5,Eggs,Dairy,3.99,30" << endl;
        outFile << "6,Chicken Meat,Meat,5.99,25" << endl;
        outFile << "7,Rice,Groceries,4.49,60" << endl;
        outFile << "8,Tomato,Vegetables,2.29,80" << endl;
        outFile << "9,Cheese,Dairy,4.79,40" << endl;
        outFile << "10,Pasta,Groceries,1.49,100" << endl;
        outFile << "11,Orange Juice,Beverages,3.29,45" << endl;
        outFile << "12,Potato,Vegetables,1.19,120" << endl;
        outFile << "13,Yogurt,Dairy,0.89,90" << endl;
        outFile << "14,Beef,Meat,8.99,20" << endl;
        outFile << "15,Water Bottle,Beverages,0.79,200" << endl;
        outFile << "16,Onion,Vegetables,0.99,110" << endl;
        outFile << "17,Coffee,Beverages,7.49,35" << endl;
        outFile << "18,Shampoo,Personal Care,6.99,40" << endl;
        outFile << "19,Toothpaste,Personal Care,3.49,60" << endl;
        outFile << "20,Chocolate Snacks,Sweets,2.99,85" << endl;
    }
    return 0;
}