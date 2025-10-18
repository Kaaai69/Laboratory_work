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
    int counter_1 = 0;
    int counter_2 = 0;
    char bukvs1[] = "aAoOuUeEyYiI";
    char bukvs2[] = "qQwWrRtTpPsSdDfFgGhHjJkKlLzZxXcCvVbBnNmM";
    for (int i = 0; i < strlen(words); i++){
        for (int j = 0; j < strlen(bukvs1); j++){
            if (words[i] == bukvs1[j]){
                counter_1++;
            }
        }
    }
    for (int i = 0; i < strlen(words); i++){
        for (int j = 0; j < strlen(bukvs1); j++){
            if (words[i] == bukvs2[j]){
                counter_2++;
            }
        }
    }
    cout << "Количество гласных букв: " << counter_1 << "\n";
    cout << "Количество согласных букв: " << counter_2 << "\n";
    return 0;

}