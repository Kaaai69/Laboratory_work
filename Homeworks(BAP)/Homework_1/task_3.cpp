#include <iostream>

using std :: cout;
int main()
{
    float temp;
    cout << "Введите температуру в градусах Цельсия: ";
    std :: cin >> temp;
    cout << "Соответствующее значение в градусах по Фаренгецту: " << temp * 9/5 + 32 << '\n';
    return 0;
}
