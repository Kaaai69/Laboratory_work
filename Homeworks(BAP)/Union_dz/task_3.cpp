#include <iostream>

using std::cout;

struct DataTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

void printDate(DataTime& date){
    cout << "Введите год: ";
    int year;
    std::cin >> year;
    date.year = year;
    cout << "Введите месяц: ";
    int month;
    std::cin >> month;
    date.month = month;
    cout << "Введите день: ";
    int day;
    std::cin >> day;
    date.day = day;
    cout << "Введите час: ";
    int hour;
    std::cin >> hour;
    date.hour = hour;
    cout << "Введите минуту: ";
    int minute;
    std::cin >> minute;
    date.minute = minute;
    cout << "Введите секунду: ";
    int second;
    std::cin >> second;
    date.second = second;
    cout << "Дата и время: " << date.year << "-" << date.month << "-" << date.day << " " << date.hour << ":" << date.minute << ":" << date.second << "\n";
}
int main()
{
    DataTime time;
    printDate(time);
}