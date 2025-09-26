#include <iostream>

using std :: cout;

int main()
{   
    int len = 10;
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
    if (index_min == 4 and index_max == 9){
        cout << "Среднее арифмитическое максимального и минимального элемента: " << ((float)max_el + (float)min_el) / 2 << '\n';

    }
    else {
        cout << "Последовательность не удовлетворяет условию\n";
    }

}