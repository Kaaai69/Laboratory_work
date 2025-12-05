#include <iostream>
#include <vector>
#include <numeric>
using std::cout;


struct Book {
    std::string name;
    std::string author;
    int year_published;
    std::string genre;
};

struct Library {
    std::vector<Book> Books;
    int amount_books;
};

void printBooks(const Book& book){
    cout << "Название книги: " << book.name << "\n";
    cout << "Имя автора книги: " << book.author << "\n";
    cout << "Год издания: " << book.year_published << "\n";
    cout << "Жанр: " << book.genre << "\n";
}
void demAllBooks(Library& library){
    for (const auto& b : library.Books){
        printBooks(b);
    }
}

void demBooks(Library& library){
    std::string author;
    cout << "Введите имя автора: ";
    std::cin >> author;
    for (auto& b: library.Books){
        if (b.author == author){
            printBooks(b);
        }
    }
}

void get_book(Library& library){
    Book book;
    std::string name;
    std::string author;
    int year_published;
    std::string genre;

    cout << "Введите название книги: ";
    std::cin >> name;

    cout << "\nВведите имя автора книги: ";
    std::cin >> author;

    cout << "\nВведите год пцбликации книги: ";
    std::cin >> year_published;

    cout << "\nВведите жанр книги: ";
    std::cin >> genre;

    book = {name, author, year_published, genre};
    library.Books.push_back(book);
    cout << "\nКнига добавлена в библиотеку!\n";
}

void pop_book(Library& library){
    std::string name;
    cout << "Введите название книги: ";
    std::cin >> name;
   
    for (auto it = library.Books.begin(); it != library.Books.end(); ++it) {
        if (it->name == name) {
            library.Books.erase(it);
            cout << "Книга удалена\n";
            return;
        }
    }
}

int main()
{   
    Library library_yes;
    int solve;
    do {
        cout << "\n- - - Меню - - - \n";
        cout << "1 - Добавить новую книгу в библиотеку.\n";
        cout << "2 - Удалить книгу по названию.\n";
        cout << "3 - Поиск книги по автору.\n";
        cout << "4 - Вывести список всех книг в библиотеке.\n";
        cout << "5 - Выйти.\n";
        cout << "Выберите операцию: ";
        std::cin >> solve;
        std::cin.ignore();
        switch (solve)
        {
            case 1: {
                get_book(library_yes);
                break;
            }
            case 2: {
                pop_book(library_yes);
                break;
            }
            case 3: {
                demBooks(library_yes);
                break;
            }
            case 4: {
                demAllBooks(library_yes);
                break;
            }
            case 5: {
                break;
            }
            default:
                cout << "Не нажимайте ерунду.\n";
                break;
        }

    } while(solve != 5);
    return 0;
}