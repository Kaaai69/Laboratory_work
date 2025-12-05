#include <iostream>
#include <vector>
#include <numeric>
using std::cout;

struct BankAccount {
    int number_acc;
    std::string owner;
    int balance;
};

void printAcc(const BankAccount& account){
    cout << "Номер счета: " << account.number_acc << "\n";
    cout << "Имя владельца счета: " << account.owner << "\n";
    cout << "Баланс: " << account.balance << "\n";
}

void demAcc(std::vector<BankAccount>& accounts){
    int number;
    cout << "Введите номер счета для показа информации: ";
    std::cin >> number;
    for (auto& b: accounts){
        if (b.number_acc == number){
            printAcc(b);
            break;
        }
    }
}
void createBank(std::vector<BankAccount>& accounts){
    BankAccount account;
    int number_acc;
    std::string owner;
    int balance = 0;
    cout << "Введите номер счета: ";
    std::cin >> number_acc;
    cout << "Введите имя владельца счета: ";
    std::cin >> owner;
    cout << "Банковский счет создан.\n";
    account = {number_acc, owner, balance};
    accounts.push_back(account);

}

void appBalance(std::vector<BankAccount>& accounts){
    int number;
    int get_app;
    cout << "Введите номер счета: ";
    std::cin >> number;
    cout << "Введите сумму пополнения: ";
    std::cin >> get_app;
    for (auto& b: accounts){
        if (b.number_acc == number){
            b.balance += get_app;
            cout << "Счет пополнен на " << get_app << " рублей.\n";
            break;
        }
    }
}
void downBalance(std::vector<BankAccount>& accounts){
    int number;
    int get_app;
    cout << "Введите номер счета: ";
    std::cin >> number;
    cout << "Введите сумму снятия: ";
    std::cin >> get_app;
    for (auto& b: accounts){
        if (b.number_acc == number && b.balance >= get_app){
            b.balance -= get_app;
            cout << "Со счета снято " << get_app << " рублей.\n";
            break;
        }
    }
}
int main()
{
    std::vector<BankAccount> Accounts;
    int solve;
    do {
        cout << "\n- - - Меню - - - \n";
        cout << "1 - Создать новый банковский счет.\n";
        cout << "2 - Пополнить счет.\n";
        cout << "3 - Снять деньги со счета.\n";
        cout << "4 - Показать информацию о счете.\n";
        cout << "5 - Выйти.\n";
        cout << "Выберите операцию: ";
        std::cin >> solve;
        std::cin.ignore();
        switch (solve)
        {
            case 1: {
                createBank(Accounts);
                break;
            }
            case 2: {
                appBalance(Accounts);
                break;
            }
            case 3: {
                downBalance(Accounts);
                break;
            }
            case 4: {
                demAcc(Accounts);
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