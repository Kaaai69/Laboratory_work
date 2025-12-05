#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>
int main() {
    std::vector<int> numbers(100000);
    for (int i = 0; i < 100000; ++i) {
        numbers[i] = i;
    }
    
    auto start1 = std::chrono::steady_clock::now();
    
    std::ofstream file1("method1.bin", std::ios::binary);
    for (int num : numbers) {
        file1.write(reinterpret_cast<const char*>(&num), sizeof(num));
    }
    file1.close();
    
    auto end1 = std::chrono::steady_clock::now();
    auto time1 = std::chrono::duration<double>(end1 - start1);
    
    auto start2 = std::chrono::steady_clock::now();
    
    std::ofstream file2("method2.bin", std::ios::binary);
    file2.write(reinterpret_cast<const char*>(numbers.data()), 
                numbers.size() * sizeof(int));
    file2.close();
    
    auto end2 = std::chrono::steady_clock::now();
    auto time2 = std::chrono::duration<double>(end2 - start2);
    
    std::cout << "Сравнение скорости записи в бинарный файл:\n";
    std::cout << "Метод 1 (по одному): " << time1.count() << " сек\n";
    std::cout << "Метод 2 (все сразу): " << time2.count() << " сек\n";
    std::cout << "Разница: " << time1.count() / time2.count() << "x быстрее\n";
    
    return 0;
}