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
    double temp1 = array[0];
    double temp2 = array[len - 1];

    array[0] = min_el; // первый элемент теперь минимальный
    array[len - 1] = max_el; // последний элемент теперь максимальный
    array[index_min] = temp1;
    array[index_max] = temp2;
    cout << "Новый массив:\n";
    for (int i = 0; i < len; i++){
        cout << array[i] << " ";
    }

}








