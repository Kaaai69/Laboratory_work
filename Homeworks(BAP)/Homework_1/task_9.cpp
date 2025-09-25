#include <iostream>

using std :: cout;
int main()
{   
    cout << "Введите натуральное число ";
    int n;
    int sum = 0;
    std :: cin >> n;
    cout << "Сумма всех чисел в соответсвие с условием: \n";
    for (int i = 1; i <= n; i++){
        if (i % 2 == 0 || i % 5 == 0){
            sum += i;
        }
    }
    cout << sum << '\n';
    return 0;
}