#include <iostream>


using std :: cout;

int main()
{
    cout << "Введите количество членов последовательности\n";    
    int n;
    std :: cin >> n;
    int array[n];
    int min_need = 0;
    int sum_chet = 0;
    for (int i = 0; i < n; i++){
        cout << "Введите " << i + 1 << " элемент последовательности\n";
        std :: cin >> array[i];
        if (array[i] % 2 != 0 && array[i] > min_need){
            min_need = array[i];
        }
        if (array[i] % 2 == 0){
            sum_chet++;
        }
    }
    cout << "Наибольшее из нечетных: " << min_need << '\n';
    cout << "Количество четных: " << sum_chet << '\n';
    return 0;
}