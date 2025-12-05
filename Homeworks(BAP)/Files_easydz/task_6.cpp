#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using std::cout;
int main()
{   
    std::string line;

    std::ofstream outFile("output.txt");
    if (outFile.is_open()){
        do {
            std::getline(std::cin, line);
            if (!line.empty()) { 
                outFile << line << "\n";
            }
        } while(!line.empty()); 
    }
    outFile.close();
    std::string lines;
    std::ifstream inFile("output.txt");
    if (inFile.is_open()){
        while (std::getline(inFile, lines)){
            cout << lines + "\n";
        }
    }
    else if (inFile.fail()){
        std::cerr << "Не удалось открыть файл!\n";
    }
    return 0;
}