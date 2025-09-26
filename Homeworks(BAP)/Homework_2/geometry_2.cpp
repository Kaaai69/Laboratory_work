#include <iostream>
#include <cmath>
#include <vector>

using std::cout;

int main()
{
    int line, column;
    cout << "Введите количество сторон многоугольника: ";
    std::cin >> line;
    cout << "\n";
    column = 2;
    int coord[line][column];
    for (int j = 0; j < line; j++){
        for (int i = 0; i < column - 1; i++){
            cout << "Введите две координаты точки:\n";
            std::cin >> coord[j][i] >> coord[j][i + 1];
        }
    }
    double summa = 0;
    for (int j = 0; j < line; j++){
        std :: vector<double> numbers;
        double x = coord[j][0];
        double y = coord[j][1];
        int k = 1;
        for (int iter = 0 ; iter < line; iter++){
            for (int i = 0; i < column - 1; i++){
                double s = pow(((coord[iter][i] - x) * (coord[iter][i] - x)) + ((coord[iter][i + 1] - y) * (coord[iter][i + 1] - y)), 0.5);
                if (s != 0){
                    numbers.emplace_back(s);
                }
            }
        }
    std :: sort(numbers.begin(), numbers.end());
    summa += (numbers[0] + numbers[1]);
    }
    cout << "\n";
    double summa_2 = summa / 2;
    cout << "\nПериметр фигуры равен: " << summa_2 << '\n';
}

 // int n;
 // int *arr = new int[n]