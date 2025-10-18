#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
using std::cout;

int main()
{
    cout << "Введите строку: ";
    std::string stroka;
    std::getline(std::cin, stroka);
    cout << "Введите подстроку: ";
    std::string under;
    std::cin >> under;
    cout << "Введите новую подстроку на замену старой подстроке: ";
    std::string under_new;
    std::cin >> under_new;
    for (int iter = 0; iter < stroka.size() - 1; iter++){
        for (int jter = iter + 1; jter < stroka.size() - 1; jter++){
            std::string substring  = stroka.substr(iter, jter + 1);
            if (substring == under){
                int i = 0;
                while (i < under_new.size()){
                    stroka[iter + i] = under_new[i];
                    i++;
                }   
            }
        }
    }
    cout << "\n" + stroka + "\n";
    return 0;
    


}