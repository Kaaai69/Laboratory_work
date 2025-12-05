#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using std::cout;
int main()
{
    std::string word;
    int count_number = 0;
    int sum = 0;
    std::ifstream inFile("test_task7.txt");
    if (inFile.is_open()){
        while (inFile >> word){
            sum+=std::stoi(word);
            count_number++;
        }
    }
    else if (inFile.fail()){
        std::cerr << "Не удалось открыть файл!\n";
    }
    cout << "В данном файле содержится: " << count_number << " слов.\n";
    cout << "Их сумма: " << sum << ".\n";
    cout << "Их среднее: " << (sum / count_number) << ".\n";
}