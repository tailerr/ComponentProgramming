#include <iostream>
#include <project/Task08/MergeSort.h>
#include <chrono>
#include <algorithm>
#include <cstdlib>

/*!
\file 
\brief Запуск сортировки слияением на массивах разной длины.

    При работе данного файла на экран выводится таблица  зависимости времени работы алгорит-
        ма от размера массива для  дальнейшего посторения графика по ней.

*/

int main(){
    
    for (unsigned long long size = 1; size < 1000000; size *= 10) {
        std::vector<int> v1(size);
        std::generate(v1.begin(), v1.end(), std::rand);
        std::vector<int> v2(v1);
        auto start = std::chrono::system_clock::now();
        merge_sort(v1.begin(), v1.end(), &my_compare);
        auto end = std::chrono::system_clock::now();
        std::cout << size <<" " << (end-start).count()<<" ";
        start = std::chrono::system_clock::now();
        parallel_merge_sort(v2.begin(), v2.end(), &my_compare);
        end = std::chrono::system_clock::now();
        std::cout<<(end-start).count()<<std::endl;
    }
    return 0;
} 