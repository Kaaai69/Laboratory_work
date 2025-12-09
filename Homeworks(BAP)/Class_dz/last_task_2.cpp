#include <iostream>
#include <vector>

using std::cout;

class Shape {
    public:
    int length;
};

class Rectangle : Shape {
    public:
    int weight;
    Rectangle(int len, int weight_t) : Shape(), weight(weight_t) {
        length = len;
    }
    void calculateArea() {
        cout << length * weight;
    }
    void calculatePerimeter() {
        cout << (length + weight) * 2;
    }
    void displayInfo() {
        cout << "Длина: " << length << ", Ширина: " << weight;
        cout << ", Площадь: ";
        calculateArea();
        cout << ", Периметр: ";
        calculatePerimeter();
        cout << "\n";
    }
};


int main()
{
    Rectangle rec(25, 10);
    rec.displayInfo();
}