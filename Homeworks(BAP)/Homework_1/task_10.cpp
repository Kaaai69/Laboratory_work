#include <iostream>

using std :: cout;
int main()
{
    cout << "Введите число: ";
    int numb;
    std :: cin >> numb;
    if (numb == 0){
        cout << "Число равно '0'\n";
    }
    else if (numb < 0){
        cout << "Число отрицательное\n";
    }
    else if (numb > 0) {
        cout << "Число положительное\n";
    }
    return 0;
}
