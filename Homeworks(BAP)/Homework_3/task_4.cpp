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
    int numbers = 1;
    for (int p = 0; p <= (line / 2); p++){ // кол-во витков спирали равно порядок матрицы пополам  
        for (int j = p; j <= line - p - 1; j++){
            array[p][j] = numbers;
            numbers++;
            if (numbers > (line * line)){
                break;
            }
        }    
            for (int i = p + 1; i < line - p; i++){
                array[i][line - p - 1] = numbers;
                numbers++;
                if (numbers >= line * line){
                    break;
                }
            }
                for (int j = line - p - 2; j >= p; j--){
                    array[line - p - 1][j] = numbers;
                    numbers++;
                    if (numbers >= line * line){
                        break;
                    }
                }
                    for (int i = line - p - 2; i >= p + 1; i--){
                        array[i][p] = numbers;
                        numbers++;
                        if (numbers >= line * line){
                            break;
                        }
                    } 
    }
    cout << "\nМатрица:\n";
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
    return 0;
}