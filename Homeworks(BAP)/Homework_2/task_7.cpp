#include <iostream>

using std :: cout;

int main()
{   
    int len = 15;
    int array[len];
    for (int i = 0; i < len; i++){
        cout << "Введите " << i + 1 << " элемент последовательности\n";
        std :: cin >> array[i];
    }
    int min_el = array[0];
    int max_el = array[0];
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
    cout << "Изначальный массив:\n";
    for (int i = 0; i < len; i++){
        cout << array[i] << " ";
    }
    cout << '\n';
    if (min_el == 0 || max_el == 0){
        cout << "Обновленный массив:\n";
        for (int i = 0; i < len; i++){
            if (i < index_min){
                cout << array[i] * 0 << " ";
            }
            else {
                cout << array[i] << " ";
            }
        }
    }
    else {
        cout << "Последовательность не удовлетворяет условию\n";
    }
    cout << '\n';

}