#include <iostream>
using std::cout;

void transpose(int **matrix, int n, int m)
{
    int** trans = new int*[m];
    for (int j = 0; j < m; j++){
        trans[j] = new int[n];
    }

     for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            trans[j][i] = matrix[i][j];
        }
    }
    
     for (int i = 0; i < m; ++i){
        for (int j = 0; j < n; ++j){
            if (j + 1 == n){
               cout << trans[i][j] << "\n"; 
            }
            else{
               cout << trans[i][j] << " ";  
            } 
        }
    }

}
int main()
{
    cout << "Пожалуйста введите количество сторок: ";
    int n, m;
    std::cin >> n;
    cout << "Пожалуйста введите количество столбцов: ";
    std::cin >> m;

    int** array = new int*[n];

    for (int i = 0; i < n; i++){
        array[i] = new int[m];
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cout << "Введите элемент " << i + 1 << " строки: "; 
            std::cin >> array[i][j];
        }
    }
    transpose(array, n, m);
    return 0;


}