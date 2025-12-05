#include <iostream>
using std::cout;

int main()
{
    cout << "Пожалуйста введите количество сторок: ";
    int n, m;
    std::cin >> n;
    cout << "Пожалуйста введите количество столбцов: ";
    std::cin >> m;
    int** array = new int*[n];

    for(int i = 0; i < n; ++i){
        array[i] = new int[m];
    }

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            cout << "Введите элемент " << i + 1 << " строки: "; 
            std::cin >> array[i][j];
        }
    }

    int sum = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            sum+= *(*(array + i) + j);
        }
    }

    cout << "\nСумма элементов массива: " << sum << "\n";

}