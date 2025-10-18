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
    char words1[50];
    cout << "Введите второе слово или набор слов через пробел: ";
    std::cin.getline(words1, 50);
    if (strlen(words) > strlen(words1))
    {
        for (int i = 0; i < strlen(words1); i++){
            char *result = strchr(words, words1[i]);
            if (result == nullptr){
                cout << "Строка не подходит под заданные условия.\n";
                break;
            }
            else if (i == strlen(words1) - 1){cout << "Строка подходит под заданные условия.\n";}
        }
    }
    else
    {
        for (int i = 0; i < strlen(words); i++){
            char *result = strchr(words1, words[i]);
            if (result == nullptr){
                cout << "Строка не подходит под заданные условия.\n";
                break;
            }
        else if (i == strlen(words) - 1){cout << "Строка подходит под заданные условия.\n";}
        }
    }
    return 0;
}