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
    std::string value;
    std::vector<double> values;
    std::map<std::string, std::vector<double>> dataMap;
    std::ifstream inFile("sensor_data.txt");
    if (inFile.is_open()){
        while (std::getline(inFile, line)){
            std::istringstream iss(line);
            iss >> value;
            values.push_back(std::stod(value));
        }
    }
    else if (inFile.fail()){
        std::cerr << "Не удалось открыть файл!\n";
    }
    values.erase(std::remove_if(values.begin(), values.end(), [](double x){return x <= -50 || x >= 50;}), values.end());
    double sum = std::accumulate(values.begin(), values.end(), 0.0);
    double sred = sum / values.size();

    std::ofstream outFile("sensor_report.txt");
    if (outFile.is_open()){
    for (const auto& val : values) {
        outFile << val << "\n";
    }
    }
    outFile << "\nСреднее значение за период: " << (sum / values.size()) << "\n";
    outFile.close();
    cout << "Анализ температурных данных завершен. Отчет сохранен в sensor_report.txt\n";
    return 0;
}