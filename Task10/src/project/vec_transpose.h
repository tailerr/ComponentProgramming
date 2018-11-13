#include<vector>
#include<stdexcept>
#include<algorithm>


template<typename T>
std::vector<T> rotate(std::vector<T> v, int angle){
    if (angle % 90 != 0)
        throw std::invalid_argument( "received angle not divisible by 90" );
    int n = (angle / 90) % 4;
    switch(n){
        case 1:
            std::reverse(v.begin(), v.end());
            v[0] *= -1;
            break;
        case 2:
            v[0] *= -1;
            v[1] *= -1;
            break;
        case 3:
            std::reverse(v.begin(), v.end());    
            v[1] *= -1;        
            break;
    }
    return v;
}