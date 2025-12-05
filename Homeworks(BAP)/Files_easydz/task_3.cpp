#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using std::cout;
int main()
{
    std::string word;
    int count_word = 0;
    std::ifstream inFile("test_task3.txt");
    if (inFile.is_open()){
        while (inFile >> word){
            count_word++;
        }
    }
    else if (inFile.fail()){
        std::cerr << "Не удалось открыть файл!\n";
    }
    cout << "В данном файле содержится: " << count_word << " слов.\n";
}