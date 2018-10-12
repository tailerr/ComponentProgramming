#include<iterator>
#include<vector>

using namespace std;

template <typename T>
bool my_compare(T lhs, T rhs)
{
    return *rhs > *lhs;
}

template <typename T>
void merge_sort(const T begin, const T end, bool(*compare)(T,T)){
    size_t dist = distance(begin, end);

    if (dist <= 1) return;
    size_t mid = dist/2;

    merge_sort(begin, begin+mid, compare);
    merge_sort(begin+mid, end, compare);

    T middle = begin+mid;
    T l = begin;
    T r = middle;

    vector<typename T::value_type> tmp(dist);
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