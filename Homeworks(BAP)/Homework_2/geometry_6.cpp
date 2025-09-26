#include <iostream>

using std::cout;

int main()
{
    int line = 2, column = 2;
    int otrezok1[line][column];
    int otrezok2[line][column];
    for (int iter = 0; iter < line; iter++){
        for (int cl = 0; cl < column - 1; cl++){
            if (iter == 0){
            cout << "Введите координаты первой точки первого отрезка: ";
            std::cin >> otrezok1[iter][cl] >> otrezok1[iter][cl + 1];
            cout << "\n";
            }
            else {
            cout << "Введите координаты второй точки первого отрезка: ";
            std::cin >> otrezok1[iter][cl] >> otrezok1[iter][cl + 1];
            cout << "\n";
            }
        }
    }
     for (int iter = 0; iter < line; iter++){
        for (int cl = 0; cl < column - 1; cl++){
            if (iter == 0){
            cout << "Введите координаты первой точки второго отрезка: ";
            std::cin >> otrezok2[iter][cl] >> otrezok2[iter][cl + 1];
            cout << "\n";
            }
            else {
            cout << "Введите координаты второй точки второго отрезка: ";
            std::cin >> otrezok2[iter][cl] >> otrezok2[iter][cl + 1];
            cout << "\n";
            }
        }
    }
    int otrez1_1[2] = {otrezok1[1][0] - otrezok1[0][0], otrezok1[1][1] - otrezok1[0][1]};
    int otrez2_2[2] = {otrezok2[1][0] - otrezok2[0][0], otrezok2[1][1] - otrezok2[0][1]};
    if ((otrez1_1[0] * otrez2_2[1] - otrez1_1[1] * otrez2_2[0]) != 0){
        cout << "Отрезки неколлинераны!\n";
    }
    else {
        cout << "Отрезки коллинераны!\n";
    }
   /* if ((((otrezok1[1][0] >= (otrezok2[1][0] or otrezok2[0][0])) and (otrezok1[0][0] <= (otrezok2[1][0] or otrezok2[0][0])) and \
(otrezok1[0][1] >= (otrezok2[0][1] or otrezok2[1][1])) and (otrezok1[1][1] <= (otrezok2[0][1] or otrezok2[1][1]))) or (((otrezok1[1][0] <= (otrezok2[1][0] or otrezok2[0][0])) and (otrezok1[0][0] >= (otrezok2[1][0] or otrezok2[0][0])) and \
(otrezok1[0][1] <= (otrezok2[0][1] or otrezok2[1][1])) and (otrezok1[1][1] >= (otrezok2[0][1] or otrezok2[1][1]))))) or \
(((otrezok2[1][0] >= (otrezok1[1][0] or otrezok1[0][0])) and (otrezok2[0][0] <= (otrezok1[1][0] or otrezok1[0][0])) and \
(otrezok2[0][1] >= (otrezok1[0][1] or otrezok1[1][1])) and (otrezok2[1][1] <= (otrezok1[0][1] or otrezok1[1][1]))) or (((otrezok2[1][0] <= (otrezok1[1][0] or otrezok1[0][0])) and (otrezok2[0][0] >= (otrezok1[1][0] or otrezok1[0][0])) and \
(otrezok2[0][1] <= (otrezok1[0][1] or otrezok1[1][1])) and (otrezok2[1][1] >= (otrezok1[0][1] or otrezok1[1][1])))))){
    cout << "Все норм\n";
    }
    else {
        cout << "Не все норм\n";
    }
    return 0; */
    int d1 = (otrezok1[1][0] - otrezok1[0][0]) * (otrezok2[0][1] - otrezok1[0][1]) - (otrezok1[1][1] - otrezok1[0][1]) * (otrezok2[0][0] - otrezok1[0][0]);
    int d2 = (otrezok1[1][0] - otrezok1[0][0]) * (otrezok2[1][1] - otrezok1[0][1]) - (otrezok1[1][1] - otrezok1[0][1]) * (otrezok2[1][0] - otrezok1[0][0]);
    cout << '\n' << d1 << " " << d2 <<  " " << otrezok1[1][0];
    if (d1 * d2 <= 0){
        cout << "\nОтрезки пересекаются!\n";
    }
    else {
        cout << "\nОтрезки не пересекаются!\n";
    }
}
