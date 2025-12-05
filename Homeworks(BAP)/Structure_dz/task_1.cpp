#include <iostream>
#include <vector>
#include <numeric>
using std::cout;

struct Employee {
    std::string name;
    int age;
    std::string post;
    int salary;
};

void printData(const Employee& employ) {
    cout << "name: " << employ.name << ", age: " << employ.age << ", post: " << employ.post << ", salary: " << employ.salary << "\n";
}
int main()
{
    cout << "Введите количество сотрудников: ";
    int n;
    Employee employ;
    std::vector<Employee> Employees;
    std::string name;
    int age;
    std::string post;
    int salary;
    std::cin >> n;
    cout << "\n";
    for (int i = 0; i < n; i++){
        cout << "Введите имя сотрудника: ";
        std::cin >> name;
        cout << "Введите возраст сотрудника: ";
        std:: cin >> age;
        cout << "Введите должность сотрудника: ";
        std:: cin >> post;
        cout << "Введите зарплату сотрудника: ";
        std:: cin >> salary;
        employ = {name, age, post, salary};
        Employees.push_back(employ);
    }
    int sum = std::accumulate(Employees.begin(), Employees.end(), 0, [](int acc, const auto& e){return acc + e.salary;});
    int older = 0;
    int younger = 100;
    Employee empl_old;
    Employee empl_young;
    for (const auto& p : Employees) {
        if (p.age > older) {
            older = p.age;
            empl_old = p;
        }
        if (p.age < younger) {
            younger = p.age;
            empl_young = p;
        }
    }
    cout << "Самый старший сотрудник: ";
    printData(empl_old);
    cout << "Самый младший сотрудник: ";
    printData(empl_young);
    cout << "Средняя зарплата всех сотрудников: " << (sum / Employees.size()) << "\n";
}