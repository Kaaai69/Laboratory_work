#include <iostream>

void free2D(int **arr, int n){
    for(int u = 0; u < n; ++u){
        delete[] arr[u];
    }
    delete[] arr;
}





using std::cout;
int main()
{
    cout << "Пожалуйста введите количество сторок: ";
    int n, m;
    std::cin >> n;
    cout << "Пожалуйста введите количество столбцов: ";
    std::cin >> m;

    int**  array = new int*[n];
    for (int i = 0; i < n; i++){
        array[i] = new int[m];
    }


    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            cout << "Введите элемент " << i + 1 << " строки: "; 
            std::cin >> array[i][j];
        }
    }

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
    free2D(array, n);

}