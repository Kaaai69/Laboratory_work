#include <iostream>
#include <string>

class BankAccount {
public:
    int accountNumber;
    std::string ownerName;
    double balance;

    BankAccount(int num, std::string name, double bal)
        : accountNumber(num), ownerName(name), balance(bal) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Пополнено: " << amount << "\n";
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Снято: " << amount << "\n";
        }
    }

    void display() const {
        std::cout << "Счет: " << accountNumber << ", Владелец: " << ownerName
                  << ", Баланс: " << balance << "\n";
    }
};

class SavingsAccount : public BankAccount {
public:
    double interestRate;

    SavingsAccount(int num, std::string name, double bal, double rate)
        : BankAccount(num, name, bal), interestRate(rate) {}

    void applyInterest() {
        double interest = balance * interestRate / 100.0;
        balance += interest;
        std::cout << "Начислены проценты: " << interest << "\n";
    }
};

int main() {
    BankAccount acc1(1001, "Иван", 5000);
    acc1.deposit(1000);
    acc1.withdraw(500);
    acc1.display();

    SavingsAccount acc2(2001, "Мария", 10000, 5.0);
    acc2.deposit(2000);
    acc2.withdraw(1000);
    acc2.applyInterest();
    acc2.display();

    return 0;