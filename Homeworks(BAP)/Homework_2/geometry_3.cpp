#include <iostream>
#include <cmath>

using std::cout;

int main()
{
    int line, column;
    line = 3;
    column = 2;
    int coord[line][column];
    for (int j = 0; j < line; j++){
        for (int i = 0; i < column - 1; i++){
            cout << "Введите две координаты точки:\n";
            std::cin >> coord[j][i] >> coord[j][i + 1];
        }
    }
    for (int j = 0; j < line; j++){
        for (int i = 0; i < column - 1; i++){
            cout << coord[j][i] << coord[j][i + 1] << "\n";
        }
    }
    double cx = (double)(coord[0][0] + coord[1][0] + coord[2][0]) / 3;
    double cy = (double)(coord[0][1] + coord[1][1] + coord[2][1]) / 3;
    cout << "\nКоордината центра массы по x: " << cx << '\n';
    cout << "\nКоордината центра массы по y: " << cy << '\n';
}

