#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
using std::cout;

int main()
{
    std::vector<double> temperature(5); // произвольное количество
    cout << "Введите 20 элементов вектора: ";
    for (auto iter = temperature.begin(); iter != temperature.end(); iter++) std::cin >> *iter;
    temperature.erase(std::remove_if(temperature.begin(), temperature.end(), [](int x){return (x > 50 or x < -50);}), temperature.end());
    auto maxi = std::max_element(temperature.begin(), temperature.end());
    auto mini = std::min_element(temperature.begin(), temperature.end());
    double sred = double(std::accumulate(temperature.begin(), temperature.end(), 0)) / temperature.size();

    cout << "Максимум: " << *maxi << "\n";
    cout << "Минимум: " <<  *mini << "\n";
    cout << "Среднее: " << std::fixed << std::setprecision(2) << sred << "\n";

    auto it = std::find_if(temperature.begin(), temperature.end(), [](int x){return x < -10;}); // возвращается индекс как я понимаю.

    if (it != temperature.end()){cout << "Не все температуры превышают - 10.\n";}
    else {cout << "Все температуры превышают -10.\n";}

    return 0;


}