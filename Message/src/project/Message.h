#include<iostream>
#include <typeinfo>
#include <sstream>

using namespace std;

void message(stringstream& f, const char *s){
    while(*s){
        if (*s=='%'){
            throw std::runtime_error("неправильный формат строки: отсутствуют аргументы");
        }
        f << *s++;
    }
}


template<typename T, typename... Args>
void message(stringstream& f, const char *s, T currValue, Args... args){
    while(*s){
        if (*s == '%'){
            f << currValue;
            s++;
            message(f, s, args...);
            return;
        }
        f << *s++;
    }
    throw std::runtime_error("неправильный формат строки: много аргументов");
}