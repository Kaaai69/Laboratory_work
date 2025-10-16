#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using std::cout;

int main()
{
    std::vector<double> fuel = {43.67, 37.12, 48.91, 32.45, 39.88, 50.00, 35.23, 46.54, 31.79, 41.03, 49.37, 34.66, 44.21, 30.50, 38.95, 47.82, 33.18, 42.74, 36.09, 45.60, 31.25, 40.68, 49.15, 35.97, 44.82, 30.00, 39.41, 48.26, 34.53, 43.08, 37.84, 46.19, 32.72, 41.55, 36.90, 45.05, 31.61, 40.16, 49.71, 35.34, 44.09, 38.44, 47.29, 33.86, 42.31, 37.56, 46.91, 32.08, 41.83, 36.28};
    auto mini = std::min_element(fuel.begin(), fuel.end());
    auto maxi = std::max_element(fuel.begin(), fuel.end());
    cout << "Минимум: " <<  *mini << "\n";
    auto test = std::find_if(fuel.begin(), fuel.end(), [maxi](int x){return x < 0.95 * *maxi;});
    if (test != fuel.end()){cout << "Уровень падал ниже заданной отметки.\n";}
    else {cout << "Уровень не падал ниже заданной отметки.\n";}
    cout << "Среднее потребление: " << fuel[0] - fuel[fuel.size() - 1] << "\n";
    std::sort(fuel.begin(), fuel.end());
    cout << "10 наибольших амплитуд для анализа: ";
    std::for_each(fuel.end() - 10, fuel.end(), [](double x){cout << x << " ";});
    cout << "\n";
    return 0;
}