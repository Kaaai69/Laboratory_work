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
    std::getline(std::cin, stroka);
    cout << "Введите еще одну строку: ";
    std::string under;
    std::getline(std::cin, under);
    int counter1_all = 0;
    int counter2_all = 0;
    std::sort(stroka.begin(), stroka.end());
    std::sort(under.begin(), under.end());
    if (stroka == under){cout << "Строки являются анаграммами!\n";}
    else {cout << "Строки не являются анаграммами!\n";}
    return 0;

}