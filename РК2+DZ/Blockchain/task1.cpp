#include <iostream>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <vector>
#include <ctime>
#include <limits>

using std::cout;
using std::endl;
using std::string;
using std::vector;

string sha256(const string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);
    std::ostringstream oss;
    for (unsigned char c : hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    }
    return oss.str();
}

class Block {
public:
    int index;
    string data;
    string previousHash;
    string hash;
    time_t timestamp;
    
    Block(int index, const string& date, const string& previousHash) 
        : index(index), data(date), previousHash(previousHash), timestamp(time(nullptr)) {
        hash = calculateHash();
    }
    
    string calculateHash() const {
        string toHash = std::to_string(index) + data + previousHash + std::to_string(timestamp);
        return sha256(toHash);
    }
    
    void printBlock() const {
        cout << "\n=== Блок #" << index << " ===" << endl;
        cout << "Временная метка: " << std::ctime(&timestamp);
        cout << "Данные: " << data << endl;
        cout << "Хеш предыдущего блока: " << previousHash << endl;
        cout << "Хеш текущего блока: " << hash << endl;
    }
};


class Blockchain {
private:
    vector<Block> chain;
    
    Block createGenesisBlock() {
        return Block(0, "Genesis Block", "0");
    }
    
public:
    Blockchain() {
        chain.push_back(createGenesisBlock());
        cout << "Блокчейн инициализирован. Создан Genesis-блок." << endl;
    }
    
    void addBlock(const string& data) {
        cout << "\nНачинаем майнинг нового блока..." << endl;
        const Block& lastBlock = chain.back();
        cout << "Хеш предыдущего блока: " << lastBlock.hash << endl;
        
        chain.emplace_back(chain.size(), data, lastBlock.hash);
        cout << "Блок успешно добавлен в цепочку!" << endl;
        cout << "Индекс нового блока: " << (chain.size() - 1) << endl;
    }
    
  
    bool isChainValid() const {
        cout << "\nПроверка целостности блокчейна..." << endl;
        

        if (chain[0].hash != chain[0].calculateHash()) {
            cout << "Ошибка: Genesis-блок поврежден!" << endl;
            return false;
        }
        
        for (size_t i = 1; i < chain.size(); ++i) {
            const Block& current = chain[i];
            const Block& previous = chain[i - 1];
            
            if (current.hash != current.calculateHash()) {
                cout << "Ошибка: Блок #" << i << " был изменен!" << endl;
                return false;
            }
            
            if (current.previousHash != previous.hash) {
                cout << "Ошибка: Несоответствие хешей между блоком #" 
                     << i << " и блоком #" << (i-1) << endl;
                return false;
            }
            
            cout << "Блок #" << i << " проверен успешно." << endl;
        }
        
        cout << "Проверка завершена. Блокчейн целостен." << endl;
        return true;
    }
    
    void printChain() const {
        cout << "\nВывод всей цепочки блоков" << endl;
        cout << "Длина цепочки: " << chain.size() << " блоков" << endl;
        
        for (const auto& block : chain) {
            block.printBlock();
        }
        
        cout << "\n=========================================" << endl;
    }

    size_t getChainSize() const {
        return chain.size();
    }
};

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void runCLI() {
    Blockchain blockchain;
    int choice = 0;
    
    do {
        cout << "\n- - - - БЛОКЧЕЙН CLI - - - - " << endl;
        cout << "1. Добавить блок (майнинг)" << endl;
        cout << "2. Проверить целостность цепочки" << endl;
        cout << "3. Вывести всю цепочку" << endl;
        cout << "4. Показать количество блоков" << endl;
        cout << "0. Выход" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Выберите действие: ";
        
        std::cin >> choice;
        
        if (std::cin.fail()) {
            cout << "Ошибка: введите число!" << endl;
            clearInputBuffer();
            continue;
        }
        
        clearInputBuffer(); 
        
        switch(choice) {
            case 1: {
                string transactionData;
                cout << "\n--- Добавление нового блока ---" << endl;
                cout << "Введите данные транзакции: ";
                std::getline(std::cin, transactionData);
                
                if (transactionData.empty()) {
                    cout << "Предупреждение: данные транзакции пусты. Используется значение по умолчанию." << endl;
                    transactionData = "Транзакция #" + std::to_string(blockchain.getChainSize());
                }
                
                blockchain.addBlock(transactionData);
                break;
            }
            
            case 2: {
                blockchain.isChainValid();
                break;
            }
            
            case 3: {
                blockchain.printChain();
                break;
            }
            
            case 4: {
                cout << "\nКоличество блоков в цепочке: " << blockchain.getChainSize() << endl;
                break;
            }
            
            case 0: {
                cout << "\nЗавершение работы блокчейн CLI..." << endl;
                cout << "Проверяем целостность перед выходом..." << endl;
                if (blockchain.isChainValid()) {
                    cout << "Блокчейн в порядке. Всего доброго!" << endl;
                } else {
                    cout << "Внимание: Обнаружены проблемы в блокчейне!" << endl;
                }
                break;
            }
            
            default: {
                cout << "Неверный выбор. Попробуйте снова." << endl;
                break;
            }
        }
        
        if (choice != 0) {
            cout << "\nНажмите Enter для продолжения...";
            std::cin.get();
        }
        
    } while (choice != 0);
}

int main() {
    cout << "=== Система Блокчейн с CLI Интерфейсом ===" << endl;
    cout << "Версия 1.0" << endl;
    cout << "Используется алгоритм хеширования: SHA-256" << endl;
    
    runCLI();
    
    return 0;
}