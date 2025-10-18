#include <iostream>


namespace firstspace
{
void insertionSort(int arr[], int size){
    for (int i = 1; i < size; i++){
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }

}
}
using std::cout;
int main()
{
    cout << "Работа с заполнением массива числами, введенными пользователем и их вывод:\n";
    int len = 10;
    int array[len];
    for (int i = 0; i < len; i++){
        cout << "Введите элемент: " << i + 1 << std::endl;
        std::cin >> array[i];
    }
    cout << "\nЭлементы массива, введенные пользователем:\n";
    for (int el = 0; el < len; el++){
        cout << array[el] << " ";

    }
    cout << "\n\nВывод суммы элементов массива и минимального числа:\n";
    int sum = 0;
    for (int j = 0; j < len; j++){
        sum += array[j];
    }
    int min_element = array[0];
    for (int j = 0; j < len; j++){
        if (array[j] < min_element){
            min_element = array[j];
        }
    }
    cout << "Сумма элементов массива: " << sum << std :: endl << "Минимальный элемент массива: " << min_element << '\n';
    cout << "\nСортировка вставками:\n";
    firstspace :: insertionSort(array, len);
    for (int u = 0; u < len; u++){
        cout << array[u] << " ";
    }
    cout << "\n";
    return 0;
}
