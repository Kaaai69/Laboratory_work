#include <iostream>
#include <algorithm>
using std::cout;

int main()
{
    int line;
    cout << "Введите порядок квадратной матрицы: ";
    std::cin >> line;
    int array[line][line];
    cout << "\nВведите элементы матрицы по строкам:\n";

    for (int i = 0; i < line; i++){
        for (int j = 0; j < line; j++){
            std::cin >> array[i][j];
        }
    }

    cout << "Изначальная матрица:\n";
    int count = 1;
    for (int i = 0; i < line; i++){
        for (int j = 0; j < line; j++){
            if (count % line == 0 and count != 0){
                cout << array[i][j] << "\n";
                count++;
            }
            else {
                cout << array[i][j] << " ";
                count++;
            }
        }
    }
    if (line % 2 == 0){
        for (int i = 0; i < (line / 2); i++){
            for (int j = 0; j < line; j++){
                std::swap(array[i][j], array[line - 1 - i][j]);
            }
        }
    }
    else {
        for (int i = 0; i < (line / 2); i++){
            for (int j = 0; j < line; j++){
                std::swap(array[i][j], array[line - 1 - i][j]);
            }
        }
    }

    cout << "Отраженная относительно горизонтальной оси:\n";
    int counter = 1;
      for (int i = 0; i < line; i++){
        for (int j = 0; j < line; j++){
            if (counter % line == 0 and counter != 0){
                cout << array[i][j] << "\n";
                counter++;
            }
            else {
                cout << array[i][j] << " ";
                counter++;
            }
        }
    }
    return 0;


}