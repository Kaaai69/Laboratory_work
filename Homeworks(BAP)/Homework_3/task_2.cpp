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

    std::vector<int> summa;
    cout << '\n';
    for (int i = 0; i < line; i++){
        int sum = 0;
        for (int j = 0; j < line; j++){
            sum += array[i][j];
        }
        summa.push_back(sum);
    }


    for (int i = 0; i < line; i++){
        int sum = 0;
        for (int j = 0; j < line; j++){
            sum += array[j][i];
        }
        summa.push_back(sum);
    }

    int sum = 0;
    for (int i = 0; i < line; i++){
        for (int j = i; j <= i ; j++){
            sum += array[i][j];
        }
    }
    summa.push_back(sum);


    int sum1 = 0;
    for (int i = 0; i < line; i++){
        for (int j = line - i - 1; j >= line - i - 1 ; j--){
            sum1 += array[i][j];
        }
    }
    summa.push_back(sum1);


    summa.erase(std::unique(summa.begin(), summa.end()), summa.end()); // оставил в векторе только уникальные элементы
    if (summa.size() == 1){
        cout << "Матрица является магической\n";
    }
    else {
        cout << "Матрица является обычной\n";
    }

}