#include <iostream>
#include <algorithm>
using std::cout;

int main()
{
    int line1, line2,  column = 2;
    cout << "Введите количество сторон большего многоугольника: ";
    std::cin >> line1;
    cout << "Введите количество сторон меньшего многоугольника: ";
    std::cin >> line2;
    int figura1[line1][column];
    int figura2[line2][column];
    for (int iter = 0; iter < line1; iter++){
        for (int cl = 0; cl < column - 1; cl++){
            cout << "Введите координаты точки первой фигуры: ";
            std::cin >> figura1[iter][cl] >> figura1[iter][cl + 1];
            cout << "\n";
        }
    }
    cout << "Следующая фигура:\n";
    for (int iter = 0; iter < line2; iter++){
        for (int cl = 0; cl < column - 1; cl++){
            cout << "Введите координаты точки второй фигуры: ";
            std::cin >> figura1[iter][cl] >> figura1[iter][cl + 1];
            cout << "\n";
        }
    }
    int d1 = (figura1[1][0] - figura1[0][0]) * (figura2[0][1] - figura1[0][1]) - (figura1[1][1] - figura1[0][1]) * (figura2[0][0] - figura1[0][0]);
    //int d2 = (otrezok1[1][0] - otrezok1[0][0]) * (otrezok2[1][1] - otrezok1[0][1]) - (otrezok1[1][1] - otrezok1[0][1]) * (otrezok2[1][0] - otrezok1[0][0]);
    int count = 0;
    for (int i = 0; i < std::max(line1, line2) - 1; i++){
        for (int j = 0; j < column - 1; j++){
            int f1_1 = figura1[i][j];
            int f1_2 = figura1[i][j + 1];
            int f2_1 = figura1[i + 1][j];
            int f2_2 = figura1[i + 1][j + 1];
            for (int i = 0; i < std::min(line1, line2) - 1; i++){
                for (int j = 0; j < column - 1; j++){
                    int d1 = (f2_1 - f1_1) * (figura2[i][j + 1] - f1_2) - (f2_2 - f1_2) * (figura2[i][j] - f1_1);
                    int d2 = (f2_1 - f1_1) * (figura2[i + 1][j + 1] - f1_2) - (f2_2 - f1_2) * (figura2[i + 1][j] - f1_1);
                    if (d1 * d2 < 0){
                        count++;
                    }
                }
            }
        }
    }
    if (count != 0){
        cout << "Многоугольники пересекаются!\n";
    }
    else {
        cout << "Многоугольники не пересекаются!\n";
    }

}