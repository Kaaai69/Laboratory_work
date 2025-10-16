#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;

int main()
{
  std::vector<int> numbers(10);
// Добавьте в начало для проверки
  #if __cplusplus >= 201103L
  std::cout << "C++11 или новее" << std::endl;
  #else
  std::cout << "Слишком старая версия C++" << std::endl;
  #endif
  cout << "Введите 10 элементов вектора: ";
  for (auto iter = numbers.begin(); iter != numbers.end(); iter++)
  {
    std::cin >> *iter;
  }
  // for (int i = 0; i < 10; i++){
  //   std::cin >> numbers[i];
  //}
  cout << "Вывод введеных пользователем элеменетов: ";
  // for (int num : numbers){
  //   cout << num << " ";
  //}
  
  std::for_each(numbers.begin(), numbers.end(), [](int x){ std::cout << x << " "; });
  cout << "\n";

  return 0;
}