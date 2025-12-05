#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>

using std::cout;
int main()
{
    std::string line;
    std::string key;
    std::string value;
    int count_line = 0;
    std::vector<double> values1;
    std::vector<double> values2;
    std::vector<double> values3;
    std::map<std::string, std::vector<double>> dataMap;
    std::ifstream inFile("test_task9.txt");
    if (inFile.is_open()){
        while (std::getline(inFile, line)){
            std::istringstream iss(line);
            iss >> key;
            iss >> value;
            if (key == "Sensor1"){
                values1.push_back(std::stod(value));
                dataMap[key] = values1;
            }
            else if (key == "Sensor2"){
                values2.push_back(std::stod(value));
                dataMap[key] = values2;
            }
            else if (key == "Sensor3"){
                values3.push_back(std::stod(value));
                dataMap[key] = values3;
            }
        }
    }
    else if (inFile.fail()){
        std::cerr << "Не удалось открыть файл!\n";
    }
    auto maxi1 = std::max_element(values1.begin(), values1.end());
    auto maxi2 = std::max_element(values2.begin(), values2.end());
    auto maxi3 = std::max_element(values3.begin(), values3.end());
    auto min1 = std::min_element(values1.begin(), values1.end());
    auto min2 = std::min_element(values2.begin(), values2.end());
    auto min3 = std::min_element(values3.begin(), values3.end());
    std::vector<double> element;
    std::vector<double> element_2;
    element.push_back(*maxi1);
    element.push_back(*maxi2);
    element.push_back(*maxi3);

    element_2.push_back(*min1);
    element_2.push_back(*min2);
    element_2.push_back(*min3);
    std::ofstream outFile("test9.txt");
    int k = 0;
    if (outFile.is_open()){
        for (const auto& pair : dataMap) {
            outFile << pair.first << ": " << "min = " << element_2[k] << ", max = " << element[k] << ", avg = " << ((element[k] + element_2[k]) / 2) << "\n";
            k++;
        }
    }
    outFile.close();
    return 0;
}