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
    cout << "Строка с заданными условиями: ";
    for (int i = 0; i < strlen(words); i++){
        if (int(words[i]) < 48 or int(words[i]) > 58){cout << words[i];}
        else{cout << "";}
    }
    cout << "\n";
    return 0;
}