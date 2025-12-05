#include <iostream>

using std::cout;


struct Rectangle {
    int wetght;
    int length;
};

struct Circle {
    int radius;
};

union Shape {
    Circle circle_model;
    Rectangle rectangle_model;
};

int main()
{
    Shape sh;
    int solve;
    do {
        cout << "Выберите фигуру (1 - круг, 2 - прямоугольник, 3 - выйти): ";
        std::cin >> solve;
        std::cin.ignore();
        switch (solve)
        {
            case 1: {
                cout << "Введите радиус круга: ";
                int numb;
                cout << "Введите целое число: ";
                std::cin >> numb;
                sh.circle_model.radius = numb;
                cout <<"Площадь круга: " << double(pow(sh.circle_model.radius, 2) * 3.14) << "\n";
                break;
            }
            case 2: {
                int numb1;
                int numb2;
                cout << "Введите длину прямоугольника: ";
                std::cin >> numb1;
                sh.rectangle_model.length = numb1;
                cout << "Введите ширину прямоугольника: ";
                std::cin >> numb1;
                sh.rectangle_model.wetght = numb1;
                cout <<"Площадь прямоугольника: " << (sh.rectangle_model.wetght * sh.rectangle_model.length) << "\n";
                break;
            }
            case 3: {
                cout << "Операция завершена!\n";
                break;
            }
            default:
                cout << "Не нажимайте ерунду.\n";
                break;
        }
    } while (solve != 3);
    return 0;
}