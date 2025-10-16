#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <stdio.h>
using std::cout;

int main()
{
    std::vector<int> numbers(20);
    cout << "Введите 20 элементов вектора: ";
    for (auto iter = numbers.begin(); iter != numbers.end(); iter++) std::cin >> *iter;
    auto maximus = std::max_element(numbers.begin(), numbers.end());
    auto mini = std::min_element(numbers.begin(), numbers.end());
    auto sred = double(std::accumulate(numbers.begin(), numbers.end(), 0)) / numbers.size();
    cout << "Максимум: " << *maximus << "\n";
    cout << "Минимум: " <<  *mini << "\n";
    cout << "Среднее: " <<  sred << "\n";
    std::sort(numbers.begin(), numbers.end());
    int len = numbers.size() / 2;
    int median = numbers[len];
    cout << "Медиана: " << median << "\n";
    return 0;


}