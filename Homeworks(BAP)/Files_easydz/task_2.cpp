#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using std::cout;
int main()
{
    std::string line;
    int count_line = 0;
    std::ifstream inFile("test_task2.txt");
    if (inFile.is_open()){
        while (std::getline(inFile, line)){
            count_line++;
        }
    }
    else if (inFile.fail()){
        std::cerr << "Не удалось открыть файл!\n";
    }
    cout << "В данном файле содержится: " << count_line << " строк.\n";
}