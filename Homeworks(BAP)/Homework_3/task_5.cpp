#include <iostream>
#include <algorithm>
#include <vector>
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
    cout << "Вывод при указанных условиях: \n";
    for (int p = 0; p <= (line / 2); p++){ // кол-во витков спирали равно порядок матрицы пополам
        for (int j = p; j <= line - p - 1; j++){
            cout << array[p][j] << " ";
        }    
            for (int i = p + 1; i < line - p; i++){
                cout << array[i][line - p - 1] << " ";
            }
                for (int j = line - p - 2; j >= p; j--){
                    cout << array[line - p - 1][j] << " ";
                }
                    for (int i = line - p - 2; i >= p + 1; i--){
                        cout << array[i][p] << " ";
                    } 
    }
    return 0;
}


