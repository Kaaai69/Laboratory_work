#include <iostream>
#include <cstring>
#include <iomanip>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
    char words[50];
    cout << "Введите слово или набор слов через пробел: ";
    std::cin.getline(words, 50);
    std::vector<int> symbols;
    cout << "Уникальные элементы строки: ";
    for (int i = 0; i < strlen(words); i++){
        symbols.push_back(int(words[i]));
    }
    std::sort(symbols.begin(), symbols.end());
    symbols.erase(std::unique(symbols.begin(), symbols.end()), symbols.end());
    for (int i : symbols) cout << char(i) << " ";
    cout << "\n";
    return 0;
}