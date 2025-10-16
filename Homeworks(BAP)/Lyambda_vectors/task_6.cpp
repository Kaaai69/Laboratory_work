#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;

int main()
{
    std::vector<int> numbers(20);
    cout << "Введите 20 элементов вектора: ";
    for (auto iter = numbers.begin(); iter != numbers.end(); iter++) std::cin >> *iter;
    auto found = std::find(numbers.begin(), numbers.end(), 7);
    if (found != numbers.end()){cout << "Семерка найдена\n";}
    else {cout << "Семерка не найдена\n";}
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(std::unique(numbers.begin(), numbers.end()), numbers.end());
    for (int x : numbers) cout << x << " ";
    cout << "\n";
    return 0;
}