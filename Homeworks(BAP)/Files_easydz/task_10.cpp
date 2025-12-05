#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <numeric>

using std::cout;
int main()
{
    std::string line;
    std::string key;
    std::string waste;
    std::string value;
    int count_measure1 = 0;
    int count_measure2 = 0;
    std::vector<double> values1;
    std::vector<double> values2;
    std::map<std::string, std::vector<double>> dataMap;
    std::ifstream inFile("power_log.txt");
    if (inFile.is_open()){
        while (std::getline(inFile, line)){
            std::istringstream iss(line);
            iss >> waste;
            iss >> key;
            iss >> value;
            if (key == "MotorA"){
                count_measure1++;
                values1.push_back(std::stod(value));
                dataMap[key] = values1;
            }
            else if (key == "PumpB"){
                count_measure2++;
                values2.push_back(std::stod(value));
                dataMap[key] = values2;
            }
        }
    }
    else if (inFile.fail()){
        std::cerr << "Не удалось открыть файл!\n";
    }
    double sum1 = std::accumulate(values1.begin(), values1.end(), 0.0);
    double sum2 = std::accumulate(values2.begin(), values2.end(), 0.0);

    std::vector<double> element;
    std::vector<int> element_2;
    element.push_back(sum1);
    element.push_back(sum2);

    element_2.push_back(count_measure1);
    element_2.push_back(count_measure2);

    std::ofstream outFile("energy_report.txt");
    int k = 0;
    if (outFile.is_open()){
        for (const auto& pair : dataMap) {
            outFile << pair.first << ": " << "measurements = " << element_2[k] << ", total = " << element[k] << "kWh, average = " << (element[k] / element_2[k]) << "kW\n";
            k++;
        }
    }
    outFile.close();
    return 0;
}