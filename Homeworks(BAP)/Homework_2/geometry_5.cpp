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
    int s = (coord[1][0] - coord[0][0]) * (coord[2][1] - coord[0][1]) - (coord[1][1] - coord[0][1]) * (coord[2][0] * coord[0][0]);
    if (s == 0){
        cout << "\nТочки лежат на одной прямой\n";
    }
    else {
        cout << "\nТочки не лежат на одной прямой\n";
    }
}
