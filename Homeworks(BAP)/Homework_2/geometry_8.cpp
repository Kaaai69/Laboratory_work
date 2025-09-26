#include <iostream>
#include <cmath>
using std::cout;

int main()
{
    int line = 2, column = 2;
    int otrezok1[line][column];
    int otrezok2[line][column];
    for (int iter = 0; iter < line; iter++){
        for (int cl = 0; cl < column - 1; cl++){
            if (iter == 0){
            cout << "Введите координаты первой точки: ";
            std::cin >> otrezok1[iter][cl] >> otrezok1[iter][cl + 1];
            cout << "\n";
            }
            else {
            cout << "Введите координаты второй точки: ";
            std::cin >> otrezok1[iter][cl] >> otrezok1[iter][cl + 1];
            cout << "\n";
            }
        }
    }
    int otrez1_1[2] = {otrezok1[1][0] - otrezok1[0][0], otrezok1[1][1] - otrezok1[0][1]};
    cout << "Длина вектора равна: " << pow(pow(otrez1_1[0], 2) + pow(otrez1_1[1], 2), 0.5) << '\n';
    return 0;

}