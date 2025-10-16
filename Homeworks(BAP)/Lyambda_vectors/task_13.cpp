#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using std::cout;

int main()
{
    std::vector<double> measure = {4.67, -0.45, 11.23, 2.89, 7.15, 12.78, 0.34, 9.56, -0.91, 5.42, 13.00, 1.77, 8.03, 3.68, 10.84, -0.12, 6.29, 12.15, 0.91, 4.26, 9.73, 2.34, 7.88, 11.47, -0.67, 5.81, 12.52, 1.45, 8.69, 3.12, 10.28, 0.58, 6.94, 11.86, -1.00, 4.93, 9.18, 2.67, 7.34, 12.41, 0.03, 5.76, 10.63, 1.89, 8.25, 3.51, 11.09, -0.23, 6.47, 12.97};
    measure.erase(std::remove_if(measure.begin(), measure.end(), [](double x){return (x < 0) or (x > 12);}), measure.end());
    auto sred = double(std::accumulate(measure.begin(), measure.end(), 0)) / measure.size();
    auto mini = std::min_element(measure.begin(), measure.end());
    auto maxi = std::max_element(measure.begin(), measure.end());
    cout << "Среднее: " <<  sred << "\n";
    cout << "Максимум: " << *maxi << "\n";
    cout << "Минимум: " <<  *mini << "\n";
    measure.erase(std::remove_if(measure.begin(), measure.end(), [](double x){return x < 8;}), measure.end());
    cout << "Значения, превыщающие 8 бар: ";
    std::for_each(measure.begin(), measure.end(), [](double x){cout << x << " ";});
    cout << "\n";
    return 0;
}