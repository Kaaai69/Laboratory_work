#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using std::cout;

int main()
{
    std::vector<double> ampl = {5.23, 1.89, 7.12, 0.45, 3.78, 6.91, 2.34, 7.55, 0.89, 4.56, 1.23, 6.78, 0.12, 5.67, 2.90, 7.01, 3.45, 6.23, 1.56, 4.89, 0.67, 7.34, 2.11, 5.89, 3.12, 6.45, 1.78, 4.23, 0.34, 7.66, 2.67, 5.01, 3.89, 6.56, 1.45, 4.78, 0.99, 7.23, 2.88, 5.44, 3.21, 6.89, 1.11, 4.45, 0.56, 7.45, 2.33, 5.78, 3.67, 6.12};
    ampl.erase(std::remove_if(ampl.begin(), ampl.end(), [](int x){return x < 0.1;}), ampl.end());
    auto sred = double(std::accumulate(ampl.begin(), ampl.end(), 0)) / ampl.size();
    auto maxi = std::max_element(ampl.begin(), ampl.end());
    auto noise = std::find_if(ampl.begin(), ampl.end(), [](int x ){return x > 0.5;});
    if (noise != ampl.end()){cout << "Не все значения превышают 0.5.\n";}
    else {cout << "Все значения превышают 0.5.\n";}
    cout << "Максимум: " << *maxi << "\n";
    cout << "Среднее: " <<  sred << "\n";
    std::sort(ampl.begin(), ampl.end());

    cout << "Десять максимальных значений: ";
    std::for_each(ampl.end() - 10, ampl.end(), [](double x ){cout << x << " ";});
    cout << "\n";
    return 0;
}