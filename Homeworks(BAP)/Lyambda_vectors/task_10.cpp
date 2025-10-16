#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using std::cout;

int main()
{
    std::vector<int> consumption(30);
    cout << "Введите 30 элементов вектора: ";
    for (auto iter = consumption.begin(); iter != consumption.end(); iter++) std::cin >> *iter;
    auto summa = std::accumulate(consumption.begin(), consumption.end(), 0);
    double sred = summa / consumption.size();
    auto maxi = std::max_element(consumption.begin(), consumption.end());
    auto mini = std::min_element(consumption.begin(), consumption.end());
    cout << "Общее потребление: " << summa << "\n";
    cout << "Среднее: " <<  sred << "\n";
    cout << "Максимум: " << *maxi << "\n";
    cout << "Минимум: " <<  *mini << "\n";
    consumption.erase(std::remove_if(consumption.begin(), consumption.end(), [sred](int x){return (x <= 1.2 * sred);}), consumption.end());
    cout << "Пиковые дни: ";
    for (int x : consumption) cout << x << " ";
    cout << "\n";
    return 0;

}