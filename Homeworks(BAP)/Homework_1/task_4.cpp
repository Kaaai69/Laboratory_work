#include <iostream>

using std :: cout;
int main()
{
    cout << "Введите число: ";
    int numb;
    std :: cin >> numb;
    if (numb % 2 == 0){
        cout << "Число четное\n";
    }
    else {
        cout << "Число нечетное\n";
    }
    return 0;
}
