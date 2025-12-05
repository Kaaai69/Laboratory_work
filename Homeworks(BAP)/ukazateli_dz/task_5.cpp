#include <iostream>
using std::cout;

int main()
{
    cout << "Пожалуйста введите количество сторок: ";
    int n, m;
    std::cin >> n;
    cout << "Пожалуйста введите количество столбцов: ";
    std::cin >> m;

    int**  array = new int*[n];
    for (int i = 0; i < n; ++i){
        array[i] = new int[m];
    }


    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            cout << "Введите элемент " << i + 1 << " строки: "; 
            std::cin >> array[i][j];
        }
    }
    
    for (int k = 0; k < n - 1; ++k){
        for (int i = 1; i < n; ++i){
            int sum1 = 0;
            int sum2 = 0;
            for (int j = 0; j < m; ++j){
                sum1+= array[i - 1][j];
                sum2+= array[i][j]; 
            }
            if (sum2 > sum1){
                int* sw = array[i - 1];
                array[i - 1] = array[i];
                array[i] = sw;
                }
        }
    }
    cout << "\nРезультат после выполненного по условию алгоритма:\n";
     for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            if (j + 1 == m){
               cout << array[i][j] << "\n"; 
            }
            else{
               cout << array[i][j] << " ";  
            } 
        }
    }
    return 0;
}