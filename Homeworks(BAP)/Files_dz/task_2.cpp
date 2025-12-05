#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using std::cout;

int main()
{
    std::ifstream File("config.txt");
    std::string line;
    std::vector<std::string> lines;
    std::string key = "timeout=";
    std::string value = "60";
    while (std::getline(File, line)){
        lines.push_back(line);
    }
    for (int i = 0; i < lines.size(); i++){
        if (lines[i].find(key) == 0){
            lines[i] = key + value;
        }
    }
    File.close();
    std::ofstream outFile("config.txt");
    if (outFile.is_open()){
        for (const auto& cur_line : lines){
            outFile << cur_line << "\n";
        }
    }
    return 0;

}