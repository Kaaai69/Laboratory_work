#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <any>
#include <typeinfo>
using namespace std;

int main()
{
    cout << "Введите количество строк и столбцов квадратой матрицы: ";
    int n;
    cin >> n;
    int array[n][n];
    int array1[n][n];
    int array2[n][n];
    int array3[n][n];
    int array4[n][n];

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
        for (int j = 0; j < n; j++){
            array1[i][j] = array[i][j];
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = i; j < n; j++){
            int temp = array1[i][j];
            array1[i][j] = array1[j][i];
            array1[j][i] = temp;
        }
    }
    cout << "Отраженная относительно главной диагонали матрица:\n";
    int counter1 = 1;
      for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (counter1 % n == 0 and counter1 != 0){
                cout << array1[i][j] << "\n";
                counter1++;
            }
            else {
                cout << array1[i][j] << " ";
                counter1++;
            }
        }
    }


    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            array2[i][j] = array[i][j];
        }
    }

    int n2 = n;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n2; j++){
            std :: swap(array2[i][j], array2[n - 1 - j][n - 1 - i]);
        }
    n2--;
    }

    cout << "Отраженная относительно побочной диагонали матрица:\n";
    int counter2 = 1;
      for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (counter2 % n == 0 and counter2 != 0){
                cout << array2[i][j] << "\n";
                counter2++;
            }
            else {
                cout << array2[i][j] << " ";
                counter2++;
            }
        }
    }


    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            array3[i][j] = array[i][j];
        }
    }

    if (n % 2 == 0){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < (n / 2); j++){
                std::swap(array3[i][j], array3[i][n - j - 1]);
            }
        }
    }
    else {
        for (int i = 0; i < n; i++){
            for (int j = 0; j < (n / 2); j++){
                std::swap(array3[i][j], array3[i][n - j - 1]);
            }
        }
    }

    cout << "Отраженная относительно вертикальной оси:\n";
    int counter3 = 1;
      for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (counter3 % n == 0 and counter3 != 0){
                cout << array3[i][j] << "\n";
                counter3++;
            }
            else {
                cout << array3[i][j] << " ";
                counter3++;
            }
        }
    }
    

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            array4[i][j] = array[i][j];
        }
    }

    if (n % 2 == 0){
        for (int i = 0; i < (n / 2); i++){
            for (int j = 0; j < n; j++){
                std::swap(array4[i][j], array4[n - 1 - i][j]);
            }
        }
    }
    else {
        for (int i = 0; i < (n / 2); i++){
            for (int j = 0; j < n; j++){
                std::swap(array4[i][j], array4[n - 1 - i][j]);
            }
        }
    }

    cout << "Отраженная относительно горизонтальной оси:\n";
    int counter4 = 1;
      for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (counter4 % n == 0 and counter4 != 0){
                cout << array4[i][j] << "\n";
                counter4++;
            }
            else {
                cout << array4[i][j] << " ";
                counter4++;
            }
        }
    }


    // проверка на совпадение
    std::vector<std::string> itog;

    int counter_final1 = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (array1[i][j] == array2[i][j]){counter_final1++;}
            else {counter_final1 = counter_final1;}
        }
    }
    std::string str1 = "12";
    if (counter_final1 == n * n){
        itog.emplace_back(str1);
    }
    else{
        itog.emplace_back(std::string("NONE"));
    }

    int counter_final2 = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (array1[i][j] == array3[i][j]){counter_final2++;}
            else {counter_final2 = counter_final2;}
        }
    }
    std::string str2 = "13";
    if (counter_final2 == n * n){
        itog.emplace_back(str2);
    }
    else{
        itog.emplace_back(std::string("NONE"));
    }


    int counter_final3 = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (array1[i][j] == array4[i][j]){counter_final3++;}
            else {counter_final3 = counter_final3;}
        }
    }
    std::string str3 = "14";
    if (counter_final3 == n * n){
        itog.emplace_back(str3);
    }
    else{
        itog.emplace_back(std::string("NONE"));
    }

    int counter_final4 = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (array2[i][j] == array3[i][j]){counter_final4++;}
            else {counter_final3 = counter_final3;}
        }
    }
    std::string str4 = "23";
    if (counter_final4 == n * n){
        itog.emplace_back(str4);
    }
    else{
        itog.emplace_back(std::string("NONE"));
    }

    int counter_final5 = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (array2[i][j] == array4[i][j]){counter_final5++;}
            else {counter_final5 = counter_final5;}
        }
    }
    std::string str5 = "24";
    if (counter_final5 == n * n){
        itog.emplace_back(str5);
    }
    else{
        itog.emplace_back(std::string("NONE"));
    }


    int counter_final6 = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (array3[i][j] == array4[i][j]){counter_final6++;}
            else {counter_final6 = counter_final6;}
        }
    }
    std::string str6 = "34";
    if (counter_final6 == n * n){
        itog.emplace_back(str6);
    }
    else{
        itog.emplace_back(std::string("NONE"));
    }
    cout << "Данные о совпадении: ";
    for (const auto& word : itog){
        cout << word << " ";
    }
    cout << '\n';
    return 0;
    
}