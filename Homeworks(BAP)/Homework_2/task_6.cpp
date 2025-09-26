#include <iostream>

using std :: cout;

int main()
{   
    int len = 15;
    double array[len];
    for (int i = 0; i < len; i++){
        cout << "Введите " << i + 1 << " элемент последовательности\n";
        std :: cin >> array[i];
    }
    cout << "Текущий массив:\n";
    for (int i = 0; i < len; i++){
        cout << array[i] << " ";
    }
    cout << '\n';
    double min_el = array[0];
    double max_el = array[0];
    int index_min = 0;
    int index_max = 0;
    for (int i = 0; i < len; i++){
        if (array[i] < min_el){
            min_el = array[i];
            index_min = i;
        }
    }
    for (int i = 0; i < len; i++){
        if (array[i] > max_el){
            max_el = array[i];
            index_max = i;
        }
    }
    cout << "Обновленный массив:\n";
    if (index_min == 1 and index_max == 0){
        for (int i = 0; i < len; i++){
            cout << array[i] / 2 << " ";
        }

    }
    else {
        cout << "Массив не удовлетворяет условию\n";
    }
}