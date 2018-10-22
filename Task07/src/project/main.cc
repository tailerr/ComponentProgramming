#include "MyBuff.h"
#include<iostream>


int main(){
    
    LineNumberBuffer b(std::cout.rdbuf());

    std::cout.rdbuf(&b);
    std::cout << std::cin.rdbuf();

    return 0;
}