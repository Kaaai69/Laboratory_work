#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using std::cout;
int main()
{
    std::string line;
    std::ifstream inFile("test_task1.txt");
    if (inFile.is_open()){
        while (std::getline(inFile, line)){
            cout << line + "\n";
        }
    }
    else if (inFile.fail()){
        std::cerr << "Не удалось открыть файл!\n";
    }
}