#include "Matrix.h"

using namespace std;

int main(){

    int* arr = new int[9];
    for (int i = 0; i<9; i++)
        arr[i] = i;


    Matrix<int> m = Matrix<int>(3, 3, {1,2,3,4,5,6,7,8,9}, 9);
    Matrix<bool> s = m || m;
    
    MaskedMatrix<int> r = MaskedMatrix<int>(m, s);
    // r = 33;
    
    return 0;
}