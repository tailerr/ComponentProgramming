#include<iterator>
#include<vector>
#include <future>
#include <thread>
#include<functional>

/*!
\file 
\brief Заголовочный файл с описанием функций

    Данный файл содержит в себе реализацию сортировки слияниеим и ее версию с параллелизацией

*/

/*! 
    Выполняет операцию сравнения
    \param [in] lhs Левый входной параметр для сравнения
    \param [in] rhs Правый входной параметр для сравнения
    \return Результат сравнения параметров, переданных в качестве аргументов
*/
template <typename T>
bool my_compare(T lhs, T rhs)
{
    return *rhs > *lhs;
}
/*! 
    Вспомогательная функция для сортировки слияния. Данная функция определяет слияние двух уже отсортированных подмассивов.
    \param [in] dist Суммарное число элементов в массивах
    \param [in] begin Начало первого массива
    \param [in] middle Конец первого и начало второго массива
    \param [in] end Конец второго массива
    \param [in] compare Функция сравнения

*/
template<typename T>
void merge(int dist, const T begin, T middle, const T end, bool(*compare)(T, T)){    
    T l = begin;
    T r = middle;
    
    std::vector<typename T::value_type> tmp(dist);
    auto k = tmp.begin();
    while(l!=middle && r!=end){
        if(compare(l, r)){
            copy(l, l+1, k);
            ++k;
            ++l;
        }
        else{
            copy(r, r+1, k);
            ++k;
            ++r;
        }
    }
    while(l!=middle){
        copy(l, l+1, k);
        ++k;
        ++l;
    }   
    while(r!=end){
        copy(r, r+1, k);
        ++k;
        ++r;
    }
    auto b = tmp.begin();
    auto e = tmp.end(); 
    copy(b, e, begin);
}
/*! 
    Сортировка слияением.
    \param [in] begin Начало первого массива
    \param [in] end Конец второго массива
    \param [in] compare Функция сравнения

*/

template <typename T>
void merge_sort(const T begin, const T end, bool(*compare)(T, T)){
    size_t dist = distance(begin, end);

    if (dist <= 1) return;
    size_t mid = dist/2;

    merge_sort(begin, begin+mid, compare);
    merge_sort(begin+mid, end, compare);
    
    
    merge(dist, begin, begin+mid, end, compare);
}

/*! 
    Сортировка слияением с параллелизацией.
    \param [in] begin Начало первого массива
    \param [in] end Конец второго массива
    \param [in] compare Функция сравнения

*/

template<typename T>
void parallel_merge_sort(const T begin, const T end, bool(*compare)(T, T)){
    int num_threads = std::thread::hardware_concurrency();
    int part_len = int(distance(begin, end)/num_threads);
    std::vector<int> points(num_threads+1);
    for (int i=0; i<num_threads;i++){
        points.at(i) = i*part_len;
    }
    points.at(num_threads) = distance(begin, end);
    std::vector<std::thread> threads(num_threads);
    std::vector<std::packaged_task<void(T, T, bool(T, T))>> merge_sort_tasks(num_threads); 
    std::vector<std::future<void>> results(num_threads);
    int iter = 0;
    for (auto& t: threads){
        merge_sort_tasks.at(iter) = std::packaged_task<void(T, T, bool(T, T))>(merge_sort<T>);
        results.at(iter) = merge_sort_tasks.at(iter).get_future();
        t = std::thread(std::move(merge_sort_tasks.at(iter)), begin+points.at(iter), begin+points.at(iter+1), compare);
        iter++;
    }
    for (auto& t : threads){
        t.join();
    }
    std::vector<std::packaged_task<void(int,const T, T, const T, bool(T, T))>> merge_tasks(int(points.size()/2));
    std::vector<std::future<void>> m_results(int(points.size()/2));
    std::vector<int> tmp;
    while(points.size() != 2){
        int i = 0;
        for (unsigned int j=0;j<points.size()-2; j+=2){
            merge_tasks.at(i) = std::packaged_task<void(int,const T, T, const T, bool(T, T))>(merge<T>);
            m_results.at(i) = merge_tasks.at(i).get_future();
            threads.at(i) = std::thread(std::move(merge_tasks.at(i)), points.at(j+2)-points.at(j), begin+points.at(j),
                begin+points.at(j+1), begin+points.at(j+2), compare);
            tmp.push_back(points.at(j));    
            i++;  
        }
        tmp.push_back(points.back());
        for (int j=0; j< i; j++)
            threads.at(j).join();
        points.swap(tmp);
        tmp.clear();    
    }
}
