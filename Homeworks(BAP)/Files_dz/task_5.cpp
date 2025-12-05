#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using std::cout;

struct Student {
    int id;
    char name[50];
    int age;
    double average_grade;
};
 void students_lovely(const Student& student){
        cout << "ID: " << student.id << "\n";
        cout << "Name: " << student.name << "\n";
        cout << "Age: " << student.age << "\n";
        cout << "Average Grade: " << student.average_grade << "\n";

}

int main()
{
    std::ofstream outFile("binary_data.dat", std::ios::binary);
    if (outFile.is_open()){
        Student student1 = {12, "David", 18, 3.8};
        Student student2 = {11, "David", 19, 4.0};
        Student student3 = {15, "David", 22, 4.8};
        outFile.write(reinterpret_cast<char*>(&student1), sizeof(Student));
        outFile.write(reinterpret_cast<char*>(&student2), sizeof(Student));
        outFile.write(reinterpret_cast<char*>(&student3), sizeof(Student));
        outFile.close();
    }
    else {
        cout << "Не получилось\n";
    }
    std::ifstream inFile("binary_data.dat", std::ios::binary);
    Student student;
    int count = 0;
    Student best_student;
    float max_ball = 0;
    if (inFile.is_open()){ // запись с каждой новой строки, аналогия с текстовыми файлами
        while(inFile.read(reinterpret_cast<char*>(&student), sizeof(Student))){
            students_lovely(student);
            if (student.average_grade > max_ball){
                max_ball == student.average_grade;
                best_student = student;
            }
        }
    }
    inFile.close();
    cout << "Самый лучший самый ути пути няша не могу одни пятеркиo(nine): \n";
    students_lovely(best_student);
    return 0;

}