#include <iostream>
#include <string>

int main()
{
    std :: cout << "Введите количество элементов в строке: \n";
    int n;
    std :: cin >> n;
    char c;
    int counter = 0;
    for (int i = 0; i < n; i++){
        std :: cout << "Введите букву;\n";
        std :: cin >> c;
        if (c == 'a' || c == 'e' || c == 'y' || c == 'u' || c == 'o' || c == 'i'){
            counter++;
        }
    }
    std::cout << "Количество гласных букв в строке равно: " << counter << '\n';

}