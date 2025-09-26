#include <iostream>
#include <math.h>

using std :: cout;

int main()
{
    cout << "Введите количество членов последовательности\n";    
    int n;
    std :: cin >> n;
    int array[n];
    int sum = 0;
    for (int i = 0; i < n; i++){
        cout << "Введите " << i + 1 << " элемент последовательности\n";
        std :: cin >> array[i];
        if (array[i] > pow(2, i + 1)){
            sum++;
        }
    }
    cout << "Количество чисел, удовлетворяющих условию: " << sum << std :: endl;
    return 0;
}
// [1, 2, 3, 4, 5]

