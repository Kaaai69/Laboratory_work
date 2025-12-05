#include <iostream>
#include <cstring>

using std::cout;
int main() {
    int word = 7;
    int maxWordLength = 20;
    
    char** words = new char*[word];
    for (int i = 0; i < word; ++i) {
        words[i] = new char[maxWordLength];
    }
    
    strcpy(words[0], "Low");
    strcpy(words[1], "Price");
    strcpy(words[2], "Flood");
    strcpy(words[3], "Virtus");
    strcpy(words[4], "Unique");
    strcpy(words[5], "Kellanis");
    strcpy(words[6], "Tarrega");

     for (int k = 0; k < word - 1; ++k){
        for (int i = 1; i < word; ++i){
            if (strlen(words[i]) > strlen(words[i - 1])){
                char* trans = words[i - 1];
                words[i - 1] = words[i];
                words[i] = trans;
            }
        }
    }
    cout << "Массив отсортированных слов: \n";
    for (int i = 0; i < word; ++i){
        cout << words[i] << " ";
    }
    cout << "\n";
}