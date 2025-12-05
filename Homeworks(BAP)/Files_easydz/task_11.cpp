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
    std::ifstream inFile("vibration_log.txt");
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
    values.erase(std::remove_if(values.begin(), values.end(), [](double x){return x <= 0.05; }), values.end());
    double sum = std::accumulate(values.begin(), values.end(), 0.0);
    double sred = sum / values.size();
    auto max = std::max_element(values.begin(), values.end());
    auto min = std::min_element(values.begin(), values.end());


    std::ofstream outFile("vibration_report.txt");
    if (outFile.is_open()){
    outFile << "Количество верных измерений: " << values.size() << "\n";
    outFile << "Фильтрованные значения(>0.05): ";
    for (const auto& val : values) {
        outFile << val << " ";
    }
    outFile << "\n";
    }
    outFile << "Среднее значение: " << (sum / values.size()) << "\n";
    outFile << "Минимум: " << *min << "\n";
    outFile << "Максимум: " << *max << "\n";
    outFile.close();
    cout << "Анализ вибрационных данных завершен. Отчет сохранен в vibration_report.txt\n";
    return 0;
}