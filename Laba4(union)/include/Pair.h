#ifndef PAIR_H
#define PAIR_H

#include <string>
#include <iostream>

template<typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;

public:
    Pair(const T1& f, const T2& s) : first(f), second(s) {}

    T1 getFirst() const { return first; }
    T2 getSecond() const { return second; }

    void setFirst(const T1& f) { first = f; }
    void setSecond(const T2& s) { second = s; }

    void display() const {
        std::cout << "(" << first << ", " << second << ")" << std::endl;
    }

    // Для использования в аналитических запросах
    static Pair<std::string, int> createProductQuantityPair(const std::string& name, int quantity) {
        return Pair<std::string, int>(name, quantity);
    }
};

#endif