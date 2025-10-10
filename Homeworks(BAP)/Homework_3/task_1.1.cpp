#include <iostream>
using namespace std;

int main()
{
    cout << "Введите количество строк и столбцов квадратой матрицы: ";
    int n;
    cin >> n;
    int array[n][n];
    cout << "Введите элементы квадратой матрицы:\n";
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> array[i][j];
        }
    }
    cout << "Изначальная матрица:\n";
    int count = 1;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (count % n == 0 and count != 0){
                cout << array[i][j] << "\n";
                count++;
            }
            else {
                cout << array[i][j] << " ";
                count++;
            }
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = i; j < n; j++){
            int temp = array[i][j];
            array[i][j] = array[j][i];
            array[j][i] = temp;
        }
    }
    cout << "Отраженная относительно главной диагонали матрица:\n";
    int counter = 1;
      for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (counter % n == 0 and counter != 0){
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