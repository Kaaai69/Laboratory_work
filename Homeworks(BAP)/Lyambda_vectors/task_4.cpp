#include <iostream>
#include <algorithm>
#include <vector>

using std::cout;


int main()
{
    std::vector<int> numbers(5);
    cout << "Введите 5 элементов вектора: ";
    for (auto iter = numbers.begin(); iter != numbers.end(); iter++) std::cin >> *iter;
    numbers.erase(std::remove_if(numbers.begin(), numbers.end(), [](int x){return x < 0;}), numbers.end());
    cout << "Вектор без отрицательных чисел: ";
    for (int x : numbers) cout << x << " ";
    cout << "\n";
    return 0;
}