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
    int SIZE = 100;
    char words[SIZE];
    cout << "Введите строку из 10 слов через пробел: ";
    std::cin.getline(words, SIZE);
    cout << std::endl << "Ответы на задачи при вводе данной строки:\n";
    const char delimiters[] = " ";
    std::string str = words;
    char *token = strtok(words, delimiters);
    int counter_of_words = 1;
    int counter_of_sovpd = 0;
    int enough = 0;
    int cnt = 0;
    int length = 0;
    cout << "Преобразованная строка с прописными символами: ";
    while (token != nullptr){
        if (token[1] == token[std::strlen(token) - 2]){counter_of_sovpd++;}
        if (token[0] == 'b'){cnt++;}
        if (std::strlen(token) > length){length = std::strlen(token);}
        if (counter_of_words == 3){
            char* str = token; // указатель на первый элемент в строке
            while (*str){ // пока у нас есть символы разыменовываем указатель и проверяем на букву.
                if (*str == 'c'){enough++;}
                str++;
            }
        }
        for (int i = 0; i < std::strlen(token); i++){
            token[i] = std::toupper(token[i]);
            cout << token[i];
        }
        cout << " ";
        token = strtok(nullptr, delimiters); // отсылает нас к следующему слову за пробелом
        counter_of_words++;
    }
    std::vector<std::string> absolut;
    std::istringstream iss(str);
    std::string word;
    std::vector<std::string> itog;
    cout << "\nНаибольшая общая подстрока(при наличии таковой): ";
    while (iss >> word){
        absolut.push_back(word);
    }
    for (int iter1 = 0; iter1 < 9; iter1++){
        for (int iter = iter1 + 1; iter < 9; iter++){
            //auto maxi = std::max_element(absolut.begin() + iter, absolut.begin() + iter + 1, [](const std::string& a, const std::string& b){return a.size() < b.size();});
            //auto mini = std::min_element(absolut.begin() + iter, absolut.begin() + iter + 1, [](const std::string& a, const std::string& b){return a.size() > b.size();});
            int lenn1 = absolut[iter1].length();
            int lenn2 = absolut[iter].length();
            std::string minim;
            std::string maxim;
            if (lenn1 > lenn2){
                maxim = absolut[iter1];
                minim = absolut[iter];
            }
            else {
                maxim = absolut[iter];
                minim = absolut[iter1];
            } 
            for (int i = 0; i < minim.length(); i++){
                int lens = 1;
                for (int j = i + 1; j < minim.length(); j++){
                        std::string substring = minim.substr(i, j + 1);
                        for (int u = 0; u < maxim.length(); u++){
                            for (int a = i + 1; a < maxim.length(); a++){
                                std::string substring1 = maxim.substr(u, a + 1);
                                if (substring1 == substring and substring.length() > lens){
                                    std::string dad = std::to_string(iter + 1);
                                    lens = substring.length();
                                    itog.push_back(substring1);
                                }
                            }
                        }
                }  
            }
        }
    }
    int maximus = 0;
    std::string ended;
    for (std::string h : itog) {
        if (h.size() > maximus){
            maximus = h.size();
            ended = h;
        }
    }
    cout << ended;
    cout << "\nКоличество слов, начинающихся с символа 'b': "<< cnt << std::endl;
    cout << "Длина самого длинного слова: "<< length << std::endl;
    cout << "Количество букв 'c' в третьем слове: " << enough << "\n";
    cout << "Количество слов, у которых совпадает второй и предпоследний символ: " << counter_of_sovpd << "\n";
    return 0;


}
