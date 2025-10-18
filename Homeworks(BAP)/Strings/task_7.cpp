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
    cout << "Введите последовательность одинаковых символов: ";
    std::cin.getline(words, 50);
    cout << "Run-Length Encoding: ";
    for (int i = 1; i < strlen(words); i++){
        int counter = 0;
        if (words[i - 1] == words[i] && words[i] != words[i + 1]){
        for (int j = 0; j < strlen(words); j++){
            if (words[j] == words[i]){
                counter++;
                if (words[j] != words[j + 1]){
                    char newr = counter + '0';
                    cout << words[j];
                    cout << newr;
                }
            }
        }
        }
    }
    cout << "\n";
}