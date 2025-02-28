#pragma once

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

class StringElem {
private:
    std::string data;
    static size_t assings;
    static size_t add;
public:
    // Конструктор по умолчанию
    StringElem() : data("") {}

    // Конструктор с инициализацией строки
    explicit StringElem(const std::string& str) : data(str) {}

    operator std::string() const {
        return data;
    }

    // Конструктор копирования
    StringElem(const StringElem& other) : data(other.data) {
        ++assings;
    }

    // Оператор присваивания (копирование)
    const StringElem& operator=(const StringElem& other) {
        ++assings;
        data = other.data;
        return *this;
    }

    // Оператор присваивания (из std::string)
    const StringElem& operator=(const std::string& other) {
        ++assings;
        data = other;
        return *this;
    }

    // Операция сложения строк
    StringElem operator+(const StringElem& other) const {
        ++add;
        return StringElem(data + other.data); // Соединение строк
    }

    // Операция сложения строки и строки
    StringElem operator+(const std::string& other) const {
        ++add;
        return StringElem(data + other); // Соединение строк
    }

    // Статический метод для сброса всех счетчиков
    static void reset() {
        assings = 0;
        add = 0;
    }

    // Статический метод для вывода статистики
    static void print() {
        size_t total = assings + add;
        std::cout << " total string operations: " << total << " assings: " << assings << " add: " << add << std::endl;
    }

    // Оператор вывода в поток
    friend std::ostream& operator<<(std::ostream& out, const StringElem& item) {
        return out << item.data;
    }
};

// Инициализация статических переменных
size_t StringElem::assings = 0;
size_t StringElem::add = 0;