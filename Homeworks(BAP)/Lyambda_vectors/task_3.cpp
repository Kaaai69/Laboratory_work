#include <iostream>
#include <algorithm>
#include <vector>

using std::cout;
int main()
{
    std::vector<int> numbers(20);
    cout << "Введите 20 элементов вектора: ";
    for (auto iter = numbers.begin(); iter != numbers.end(); iter++) std::cin >> *iter;
    cout << "Максимальный элемент вектора: ";
    auto maxi = std::max_element(numbers.begin(), numbers.end(), [](int a, int b){return a < b;}); // макс/мин находит указатель, разыменовка обязательна 
    cout << *maxi;
    cout << "\n";
    return 0;
}