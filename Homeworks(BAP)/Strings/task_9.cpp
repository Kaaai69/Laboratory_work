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
    cout << "Введите первое слово: ";
    std::cin.getline(words, 50);
    char words1[50];
    cout << "Введите второе слово: ";
    std::cin.getline(words1, 50);
    std::string stroka = words1;
    std::string stroka1 = words;
    std::vector<std::string> itog;
    if (strlen(words) > strlen(words1))
    {
        for (int i = 0; i < strlen(words1); i++){
            for (int j = i + 1; j < strlen(words1); j++){
                std::string substring = stroka.substr(i, j + 1);
                for (int u = 0; u < strlen(words); u++){
                    for (int a = i + 1; a < strlen(words); a++){
                        std::string substring1 = stroka1.substr(u, a + 1);
                        if (substring1 == substring){
                            itog.push_back(substring1);
                        }
                    }
                }
            }  
        }
    }
    else
    {
        for (int i = 0; i < strlen(words); i++){
            for (int j = i + 1; j < strlen(words); j++){
                std::string substring = stroka1.substr(i, j);
                for (int u = 0; u < strlen(words1); u++){
                    for (int a = i + 1; a < strlen(words1); a++){
                        std::string substring1 = stroka.substr(u, a);
                        if (substring1 == substring){
                            itog.push_back(substring1);
                        }
                    }
                }
            }  
        }
    }
    //for (std::string h : itog) cout << h << " ";
    int max_length = 0;
    int index_new = 0;
    std::string itog_t;
    for (int iter = 0; iter < itog.size(); iter++){
        if (itog[iter].size() > max_length){
            max_length = itog[iter].size();
            index_new = iter;
        }
    }

    cout << itog[index_new] << "\n";
    return 0;

}