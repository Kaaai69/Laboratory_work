#include <iostream>

void ost(int numb){
    std :: cout << "Введите количество остановок, пожалуйста!!\n";
    int numb_of_stops;
    std :: cin >> numb_of_stops;
    for (int i = numb_of_stops; i == numb_of_stops; i++){
        if (numb_of_stops < 0){
            std :: cout << "Не вводите ерунду\n";
        }
        else if (numb_of_stops == i){
            std :: cout << "Плата за проезд: " << i * 5 << std :: endl; 
        }
    }


}
int main() {
    std :: cout << "Введите температуру на улице:\n";
    int n;
    std :: cin >> n;
    if (n < 0) {
        std :: cout << "Наденьте зимнюю одежду, пожалуйста!";
    }
    else if (0 <= n and n <= 10) {
        std :: cout << "Наденьте теплую одежду, пожалуйста!";
    }
    else if (10 < n  and n <= 20) {
        std :: cout << "Наденьте легкую одежду, пожалуйста!";
    }
    else if (n > 20) {
     std :: cout << "Наденьте летнюю одежду, пожалуйста!";
    }
    std :: cout << "\n\n";
    :: ost(n);
    return 0;
}


