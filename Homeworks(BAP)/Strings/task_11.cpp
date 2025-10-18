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
    cout << "Введите k: ";
    int k;
    std::cin >> k;
    std::string stroka = words;
    std::vector<std::string> local;
    for (int i = 0; i < strlen(words) - 1; i++){
        for (int j = i + 1; j < strlen(words) - 1; j++){
            std::string substring = stroka.substr(i, j + 1);
            if (substring.size() == k){
                int summa = 0;
                for (int iter = 0; iter < substring.size(); iter++){
                    auto counter = std::count(substring.begin(), substring.end(), substring[iter]);
                    summa += counter;
                }
                if (summa == substring.size()){
                    local.push_back(substring);
                }
                //std::sort(substring.begin(), substring.end());
                //substring.erase(unique(substring.begin(), substring.end()), substring.end());
            }
        }
    }
    for (std::string s : local) cout << s << " ";
    cout << "\n";
    return 0;  
    
}