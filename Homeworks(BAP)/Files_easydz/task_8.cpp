#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using std::cout;
int main()
{
    std::string line1;
    std::string line2;
    int count_line = 0;
    int count_yes_line = 0;
    std::ifstream outFile1("file1.txt");
    std::ifstream outFile2("file2.txt");
    if (outFile1.is_open() && outFile2.is_open()){
        while (std::getline(outFile1, line1) && std::getline(outFile2, line2)){
            count_line++;
            if (line1 != line2) {
                cout << "Не все строки файла совпадают\n";
                break;
            }
            else {
                count_yes_line++;
            }
        }
    }
    else if (outFile1.fail() || outFile2.fail()){
        std::cerr << "Не удалось открыть файл!\n";
    }
    if (count_line == count_yes_line) {
        cout << "Все строки файла совпадают\n";
    }
}