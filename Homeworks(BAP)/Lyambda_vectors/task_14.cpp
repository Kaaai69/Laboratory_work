#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
using std::cout;

int main()
{
    std::vector<double> consumption =  {345, 187, 423, 256, 398, 112, 467, 289, 154, 431, 203, 376, 145, 492, 267, 324, 178, 445, 231, 387, 164, 478, 295, 412};
    auto summa = std::accumulate(consumption.begin(), consumption.end(), 0);
    long double sred = double(summa) / consumption.size();
    auto maxi = std::max_element(consumption.begin(), consumption.end());
    cout << "Общее потребление: " << summa << "\n";
    cout << "Среднее: " <<  sred << "\n";
    cout << "Максимум: " << *maxi << "\n";
    std::vector<long double> deviation(consumption.size());
    std::transform(consumption.begin(), consumption.end(), deviation.begin(), [sred](long double x){return double(sred - x);});
    cout << "Отклонения каждого часа от среднего: ";
    for (double x : deviation) cout << std::fixed << std::setprecision(2) << std::abs(x) << " ";
    std::sort(consumption.begin(), consumption.end());
    cout << "\n5 минимальных часов потребления: ";
    std::for_each(consumption.begin(), consumption.begin() + 5, [](int x ){cout << x << " ";});
    cout << "\n";
    return 0;
}