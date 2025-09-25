#include <iostream>

using std :: cout;
int main()
{   
    cout << "Введите натуральное число ";
    int n;
    std :: cin >> n;
    cout << "Квадраты всех чисел в соответсвие с условием: \n";
    for (int i = 1; i <= n; i++){
        cout << i * i << '\n';
    }
    return 0;
}


