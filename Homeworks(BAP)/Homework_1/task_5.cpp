#include <iostream>

using std :: cout;
int main()
{
    cout << "Введите число: ";
    int numb;
    std :: cin >> numb;
    if (numb % 3 == 0 and numb % 5 == 0){
        cout << "Число делится на 3 и на 5\n";
    }
    else if (numb % 3 == 0){
        cout << "Число делится на 3\n";
    }
    else if (numb % 5 == 0) {
        cout << "Число делится на 5\n";
    }
    else {
        cout << "Число не делится ни на одно из предложенных чисел\n";
    }
    return 0;
}
