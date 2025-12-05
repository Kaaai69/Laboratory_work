#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using std::cout;

int main()
{
    std::string line;
    std::ifstream inFile("book.txt");
    std::ofstream outfile("outFile.txt");
    std::vector<std::pair<int, int>> positions;
    if (outfile.is_open()){
        int count_word = 0;
        int number_str = 1;
        if (inFile.is_open()){
            while(std::getline(inFile, line)){
                std::streampos line_start = inFile.tellg() - static_cast<std::streampos>(line.length()) - 1;
                std::stringstream ss(line);
                std::string cell;
                while (std::getline(ss, cell, ' ')){
                    if (cell == "герой"){
                        std::streampos position = inFile.tellg();
                        size_t posiiton_word = line.find("герой");
                        count_word++;
                        outfile << cell << ": номер строки " << number_str << ", позиция в строке "<< static_cast<int>(posiiton_word) << "\n";
                    }
                    cout << "[" << cell << "]";
                }
                cout << "\n";
            number_str++;  
            }
            outfile << "Общее количество найденных слов: " << count_word;   
        }
        outfile.close();
        inFile.close();
    }
    return 0;
}