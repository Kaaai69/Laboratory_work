#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using std::cout;

int main()
{ 
  std::vector<int> numbers(10);
  cout << "Введите 10 элементов вектора: ";
  for (auto iter = numbers.begin(); iter != numbers.end(); iter++){std::cin >> *iter;}
  cout << "Новые 10 элементов вектора: ";
  std::for_each(numbers.begin(), numbers.end(), [](int x){cout << pow(x, 2) << " ";});
  cout << "\n";
  return 0;
}