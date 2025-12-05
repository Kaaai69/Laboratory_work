#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using std::cout;
int main()
{
    char ch;
    int count_symb = 0;
    std::ifstream inFile("input.txt");
    if (inFile.is_open()){
        while (inFile.get(ch)){
            count_symb++;
        }
    }
    else if (inFile.fail()){
        std::cerr << "Не удалось открыть файл!\n";
    }
    cout << "В данном файле содержится: " << count_symb << " символов.\n";
}