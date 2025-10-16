#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using std::cout;

int main()
{
    std::vector<int> power(20);
    cout << "Введите 20 элементов вектора: ";
    for (auto iter = power.begin(); iter != power.end(); iter++) std::cin >> *iter;
    power.erase(std::remove_if(power.begin(), power.end(), [](int x ){return x < 0;}), power.end());
    auto maxi = std::max_element(power.begin(), power.end());
    auto mini = std::min_element(power.begin(), power.end());
    auto sred = double(std::accumulate(power.begin(), power.end(), 0)) / power.size();
    auto work_all = std::find_if(power.begin(), power.end(), [](int x){return (x >= 10 && x <= 90);});
    if (work_all != power.end()){cout << "Двигатель не всегда работал в указанных пределах.\n";}
    else {cout << "Двигатель всегда работал в указанных пределах.\n";}
    cout << "Максимум: " << *maxi << "\n";
    cout << "Минимум: " <<  *mini << "\n";
    cout << "Среднее: " <<  sred << "\n";
    std::sort(power.begin(), power.end());
    int median = power[power.size() / 2];
    cout << "Медиана: " << median << "\n";
    return 0;
}