#pragma once
#include <iostream>
#include <string>

template<typename T>
class Logger {
public:
    static void log(const std::string& message) {
        std::cout << "[" << typeid(T).name() << "] " << message << std::endl;
    }

    static void log(const T& value) {
        std::cout << "[" << typeid(T).name() << "] " << value << std::endl;
    }
};