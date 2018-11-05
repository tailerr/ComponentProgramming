#include "MyBuff.h"
#include<iostream>


int main(){
    
    std::streambuf* oldbuf = std::cout.rdbuf();
    LineNumberBuffer b(std::cout.rdbuf());

    std::cout.rdbuf(&b);
    std::cout << std::cin.rdbuf();
    std::cout.rdbuf(oldbuf);

    return 0;
}