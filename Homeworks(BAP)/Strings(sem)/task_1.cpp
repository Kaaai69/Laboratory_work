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
    auto maximus = std::max_element(words.begin(), words.end(), [](std::string first, std::string second){return first.size() < second.size();});
    cout << "Самое длинное слово в строке: " << *maximus << "\n";
    return 0;
}