#include <iostream>
#include <cstring>
#include <iomanip>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

bool isPalindrome(const char* str){
    int length = strlen(str);
    for (int i =  0; i < strlen(str); i++){
        if (str[i] != str[length - 1 - i]){
            return false;
        }
    }
    return true;
}

int main()
{
    const int SIZE = 50;
    char words[SIZE];
    cout << "Введите слово или набор слов через пробел: ";
    std::cin.getline(words, SIZE);
    if (isPalindrome(words)){cout << "Строка является палиндромом.\n";}
    else {cout << "Строка не является палиндромом.\n";}
    return 0;

}