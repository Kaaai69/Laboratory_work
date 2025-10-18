#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
using std::cout;

int main()
{
    cout << "Введите строку: ";
    std::string stroka;
    char symbol;
    std::getline(std::cin, stroka);
    cout << "\nВведите символ: ";
    std::cin >> symbol;
    stroka.erase(std::remove(stroka.begin(), stroka.end(), symbol));
    cout << stroka + "\n";
    return 0;
}