#include <iostream>
#include <algorithm>
#include <cmath>
using std::cout;

int main()
{
    int theta;
    theta = theta * M_PI / 180.0;
    cout << "Введите координаты первой точки: ";
    int x, y, u;
    std::cin >> x >> y;
    cout << "Введите угол поворота точки в градусах: ";
    std::cin >> u;
    double x_new = cos(theta) * x + sin(theta) * y;
    double y_new = -sin(theta) * x + cos(theta) * y;
    cout << "Новые координаты точек: x = " << x_new << ", y = " << y_new << "\n";
    return 0;

}