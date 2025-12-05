#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using std::cout;
int main()
{
    std::string line;
    std::ifstream inFile("source.txt");
    std::ofstream outFile("copy.txt");
    if (inFile.is_open()){
        while (std::getline(inFile, line)){
            if (outFile.is_open()){
                outFile << line << "\n";
            }
            else {
                std::cerr << "ЛОШАРА\n";
            }
        }
    }
    else if (inFile.fail()){
        std::cerr << "Не удалось открыть файл!\n";
    }
    inFile.close();
    outFile.close();
    cout << "Успешно перезаписано!\n";
}