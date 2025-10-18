#include <iostream>
#include <algorithm>

using std::cout;

int main()
{
    cout << "Введите координаты первой точки: ";
    int a1, a2, b1, b2, c1, c2;
    int a3 = 1;
    int c3 = 1;
    int b3 = 1;
    std::cin >> a1 >> a2;
    cout << "Введите координаты второй точки: ";
    std::cin >> b1 >> b2;
    cout << "Введите координаты второй точки: ";
    std::cin >> c1 >> c2;
    double det = (a1 * b2 * c3 + b1 * c2 * a3 + a2 * b3 * c1 - a3 * b2 * c1 - b3 * c2 * a1 - a2 * b1 * c3);
    double s = std::abs(0.5 * det);
    cout << "Плоащдь треугольника равна: " << s << "\n";
    return 0;
}