#include <iostream>

using std :: cout;
int main()
{
    cout << "Введите свой возраст: ";
    int old;
    std :: cin >> old;
    if (old < 18 && old >= 0){
        cout << "Вы еще ребенок и вам нет 18 лет\n";
    }
    else if (old > 18 && old <= 60){
        cout << "Вы уже взрослый\n";
    }
    else if (old > 60) {
        cout << "Вы уже пожилой\n";
    }
    else {
        cout << "Не вводи ерунду.\n";
    }
    return 0;
}
