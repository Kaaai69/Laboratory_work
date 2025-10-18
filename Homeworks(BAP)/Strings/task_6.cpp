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
    cout << "Введите первое слово или набор слов через пробел: ";
    std::cin.getline(words, 50);
    cout << "Введите величину сдвига: ";
    int n;
    std::cin >> n;
    cout << "Зашифрованная строка: ";
    for (int i = 0; i < strlen(words); i++){
        if ((int(words[i]) > 64 && int(words[i]) < 91) || (int(words[i]) > 96 && int(words[i]) < 123)){
            cout << char(int(words[i]) + n);
        }
        else {cout << words[i];}
    }
    cout << "\n";
    
}