#include <iostream>

using std :: cout;

int main()
{
    cout << "Введите длину и ширину прямоугольника: ";
    int length, width;
    std :: cin >> length >> width;
    cout << "Площадь прямоугольника равна: " << length * width << '\n';
    return 0;
}