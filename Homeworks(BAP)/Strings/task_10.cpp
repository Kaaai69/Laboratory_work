#include <iostream>
#include <cstring>
#include <iomanip>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;


int main()
{
    char words[50];
    cout << "Введите строку: ";
    std::cin.getline(words, 50);
    const char delimiters[] = " ";
    std::string end;
    char *token = strtok(words, delimiters);
    while (token != nullptr){
        for (int iter = 0; iter < strlen(token) / 2; iter++){
            std::swap(token[iter], token[strlen(token) - iter - 1]);
        }
        std::string wow = token;
        end += wow;
        end += " ";
        token = strtok(nullptr, delimiters);
    }
    cout << end << "\n";
    return 0;
}