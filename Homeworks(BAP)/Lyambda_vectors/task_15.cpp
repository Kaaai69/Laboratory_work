#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
using std::cout;

int main()
{
    std::vector<std::vector<double>> temp(5, std::vector<double>(30));
    std::vector<std::vector<double>> pressure(5, std::vector<double>(100));


    cout << "Введите элементы каналов температуры:\n";
    for (auto iter = 0; iter < 5; iter++){
        cout << "Элементы " << iter + 1 << " канала (в каждом канале 30 элементов): ";
        for (auto under = 0; under < 30; under++){
            std::cin >> temp[iter][under]; 
        }
    }

    cout << "\n";
    cout << "Введите элементы каналов давления:\n";
    for (auto iter = 0; iter < 5; iter++){
        cout << "Элементы " << iter + 1 << " канала (в каждом канале 100 элементов): ";
        for (auto under = 0; under < 100; under++){
            std::cin >> pressure[iter][under]; 
        }
    }
    // среднее по температуре 
    cout << "\n";
    for (auto iter = 0; iter < 5; iter++){
        cout << "Средняя температура " << iter + 1 << " канала:\n";
        auto sred = double(std::accumulate(temp[iter].begin(), temp[iter].end(), 0)) / temp[iter].size();
        cout << sred << "\n";
    }

    // макс мин давление 
    cout << "\n";
    for (auto iter = 0; iter < 5; iter++){
        cout << "Максимальное и минимальное давление " << iter + 1 << " канала:\n";
        auto mini = std::min_element(pressure[iter].begin(), pressure[iter].end());
        auto maxi = std::max_element(pressure[iter].begin(), pressure[iter].end());
        cout << "Максимум: " << *maxi << "\n";
        cout << "Минимум: " <<  *mini << "\n";
    }

    // разности между соседними измерениями температуры
    cout << "\n";
    for (auto iter = 0; iter < 5; iter++){
        std::vector<double> det_temp(temp[iter].size());
        cout << "Разности температур " << iter + 1 << " канала:\n";
        std::adjacent_difference(temp[iter].begin(), temp[iter].end(), det_temp.begin());
        for (double x : det_temp) cout << x << " ";
        cout << "\n";
    }



    // разности между соседними измерениями давления
    cout << "\n";
    for (auto iter = 0; iter < 5; iter++){
        std::vector<double> det_temp(pressure[iter].size());
        cout << "Разности давлений " << iter + 1 << " канала:\n";
        std::adjacent_difference(pressure[iter].begin(), pressure[iter].end(), det_temp.begin());
        for (double x : det_temp) cout << x << " ";
        cout << "\n";
    }

    // определение канала с наибольшей вариацией температуры
    cout << "\n";
    double delta = 0;
    int canal_temp = 0;
    for (auto iter = 0; iter < 5; iter++){
        cout << "Разности температур " << iter + 1 << " канала:\n";
        auto maxi = std::max_element(temp[iter].begin(), temp[iter].end());
        auto mini = std::min_element(temp[iter].begin(), temp[iter].end());
        if (maxi - mini > delta){
            delta = maxi - mini;
            canal_temp = iter + 1;
        }
    }
    cout << "Канал с наибольшей вариацией температуры: " << canal_temp << "\n";


    // определение канала с наибольшей вариацией давления
    double delta_press = 0;
    int canal_press = 0;
    for (auto iter = 0; iter < 5; iter++){
        cout << "Разности температур " << iter + 1 << " канала:\n";
        auto maxi = std::max_element(pressure[iter].begin(), pressure[iter].end());
        auto mini = std::min_element(pressure[iter].begin(), pressure[iter].end());
        if (maxi - mini > delta){
            delta_press = maxi - mini;
            canal_press = iter + 1;
        }
    }
    cout << "Канал с наибольшей вариацией температуры: " << canal_press << "\n";
    

    // нормализация давления 
    cout << "\n";
    for (auto iter = 0; iter < 5; iter++){
        std::vector<double> normalize(pressure[iter].size());
        cout << "Нормализованные значения, подходящие под условия" << iter + 1 << " канала:\n";
        auto mini = std::min_element(pressure[iter].begin(), pressure[iter].end());
        auto maxi = std::max_element(pressure[iter].begin(), pressure[iter].end());
        auto mx = *maxi;
        auto mn = *mini;
        std::transform(pressure[iter].begin(), pressure[iter].end(), normalize.begin(), [mx, mn](int x){return (x - mn) / (mx - mn);});
        for (double x : normalize) {
            if (x > 0.9){cout << x << " ";}
        }
        cout << "\n";  
    }
    // канал с наибольшим средним значением температуры
    cout << "\n";
    double sred_mx = 0;
    int index_sred = 0;
    for (auto iter = 0; iter < 5; iter++){
        auto sred = double(std::accumulate(temp[iter].begin(), temp[iter].end(), 0)) / temp[iter].size();
        if (sred > sred_mx){
            sred_mx = sred;
            index_sred = iter + 1;
        }
    }
    cout << "Канал с наибольшей средней температурой: " << index_sred << "\n";
    return 0; 
}