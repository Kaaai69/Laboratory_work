#include <iostream>
#include <vector>

using std::cout;

class Publication {
    public:
    std::string name;
};

class Book : public Publication {
    public:
    std::string author;
    int year_published;
    Book(const std::string& book_name, const std::string& author_name, int year) : Publication(), author(author_name), year_published(year) {
        name = book_name;
        cout << "Создан объект Book!\n";
    }
    void displayInfo() {
        cout << "Название: " << name << ", Автор: " << author << ", Год выпуска: " << year_published << ".\n"; 
    }

};


int main()
{
    Book book1("Идиот","Вася", 1897);
    book1.displayInfo();
    return 0;
}