#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
using std::cout;

int main()
{
    cout << "Введите строку: ";
    std::string stroka;
    std::getline(std::cin, stroka);
    std::vector<std::string> words;
    std::string word1;
    std::istringstream iss(stroka);
    while (iss >> word1){
        words.push_back(word1);
    }
    cout << "Вывод каждого слова строки в отдельную строчку:\n";
    for (std::string s : words) cout << s + "\n";
    return 0;
}