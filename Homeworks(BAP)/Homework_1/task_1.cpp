#include <iostream>

using std :: cout;
int main()
{
    int length;
    cout << "Введите длину в сантиметрах: ";
    std :: cin >> length;
    cout << "Метры: " << length / 100 << " Сантиметры: " << length % 100 << '\n';
    return 0;
}

