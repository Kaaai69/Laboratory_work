#include <iostream>

using std::cout;
union Variant {
    int number;
    double number_2;
    char symbol;
};

int main()
{   
    char s;
    Variant var;
    do {
        cout << "Выберите тип данных (i - целое число, d - число с плавающей запятой, c - символ, q - выйти): ";
        std::cin >> s;
        std::cin.ignore();
        switch (s)
        {
            case 'i': {
                int numb;
                cout << "Введите целое число: ";
                std::cin >> numb;
                var.number = numb;
                cout <<"Вы ввели число: " <<var.number << "\n";
                break;
            }
            case 'd': {
                double numb;
                cout << "Введите число с плавающей запятой: ";
                std::cin >> numb;
                var.number_2 = numb;
                cout << var.number_2;
                cout <<"Вы ввели число c плавающей запятой: " << var.number_2 << "\n";
                break;
            }
            case 'c': {
                char symb;
                cout << "Введите число с плавающей запятой: ";
                std::cin >> symb;
                var.symbol = symb;
                cout << var.symbol;
                cout <<"Вы ввели символ: " <<var.symbol << "\n";
                break;
            }
            case 'q': {
                cout << "Операция завершена!\n";
                break;
            }
            default:
                cout << "Не нажимайте ерунду.\n";
                break;
        }
    } while (s != 'q');
    return 0;

}