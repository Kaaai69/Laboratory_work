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
    cout << "Введите строку: ";
    std::cin.getline(words, 50);
    words[0] =toupper(words[0]);
    cout << "Измененная строка: ";
    for (int i = 0; i < strlen(words); i++){
        cout << words[i];
        if (words[i] == char(46) || words[i] == char(63) || words[i] == char(33)){
            for (int j = i + 1; words[j] == char(32); j++){
                char hah = toupper(words[j + 1]);
                i++;
                cout << " " << hah;
            }
        }
    }
    cout << "\n";
    return 0;
}