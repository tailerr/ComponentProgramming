#include <iostream>

using namespace std;

template <typename T>
class MaskedMatrix;


template <typename T>
class Matrix;



template <typename T>
class Matrix{
    private:
        T **_data;
        int _n;
        int _m;
    public:
        template <typename U>
        friend class MaskedMatrix;
        template <typename U>
        friend const bool operator==(Matrix<T> const m1, Matrix<T> const m2);
        Matrix<T>(int n, int m, initializer_list<T> data, int dataSize){
            if (dataSize!= n*m) throw out_of_range("Matrix::constructor");
            _n = n;
            _m = m;
            _data = new T*[n];
            auto k = data.begin();
	        for (int i = 0; i<n; ++i) {
		        _data[i] = new T[m];
		        for (int j = 0; j<m; ++j) {
			        _data[i][j] = *k;
                    k++;
			    }
	        }
        }
        Matrix<T>(int n, int m, T* data, int dataSize){
            if (dataSize!= n*m) throw out_of_range("Matrix::constructor");
            _n = n;
            _m = m;
            _data = new T*[n];
	        for (int i = 0; i<n; ++i) {
		        _data[i] = new T[m];
		        for (int j = 0; j<m; ++j) {
			        _data[i][j] = data[i*n+j];
			    }
	        }
        }
        Matrix<T>(int n, int m){
            _n = n;
            _m = m;
            _data = new T*[n];
	        for (int i = 0; i<n; ++i) 
		        _data[i] = new T[m];
		    
        }
        Matrix(const Matrix<T> & v){
            _n = v._n;
            _m = v._m;
            _data = new T* [_n];
            
            for (int i = 0; i< _n; ++i) {
		        _data[i] = new T[_m];
		        for (int j = 0; j<_m; ++j) {
			        _data[i][j] = v._data[i][j];
			    }
            }
        }
        ~Matrix(){
            delete [] _data;
        }
        Matrix<T>& operator=(const Matrix<T> & v){
            _n = v._n;
            _m = v._m;
            delete [] _data;
            _data = new T*[_n];
	        for (int i = 0; i<_n; ++i) {
		        _data[i] = new double[_m];
		        for (int j = 0; j<_m; ++j) {
			        _data[i][j] = v._data[i*_n+j];
			    }
	        }
            return *this;
        }

        Matrix<T> operator+(Matrix<T> const& b){
            if (_n ==b._n && _m==b._m){
                Matrix<T> result = Matrix<T>(*this);
                for(int i = 0; i<_n; i++)
                    for (int j=0;j<_m;j++){
                        result._data[i][j] += b._data[i][j];
                    }
                return result;
            }
            else{
                throw out_of_range("Matrix::operator+");
            }
        }

        Matrix<T> operator-(Matrix<T> const& b){
            if (_n ==b._n && _m==b._m){
                Matrix<T> result = Matrix<T>(*this);
                for(int i = 0; i<_n; i++)
                    for (int j=0;j<_m;j++){
                        result._data[i][j] -= b._data[i][j];
                    }
                return result;
            }
            else{
                throw out_of_range("Matrix::operator-");
            }
        }
         Matrix<T> operator*(Matrix<T> const& b){
            if (_n ==b._n && _m==b._m){
                Matrix<T> result = Matrix<T>(*this);
                for(int i = 0; i<_n; i++)
                    for (int j=0;j<_m;j++){
                        result._data[i][j] *= b._data[i][j];
                    }
                return result;
            }
            else{
                throw out_of_range("Matrix::operator*");
            }
        }

         Matrix<T> operator/(Matrix<T> const& b){
            if (_n ==b._n && _m==b._m){
                Matrix<T> result = Matrix<T>(*this);
                T * res = new T[_n*_m];
                for(int i = 0; i<_n; i++)
                    for (int j=0;j<_m;j++){
                        res[i*_n+j] = _data[i][j] / b._data[i][j];
                    }
                return Matrix<T>(_n, _m, res, _n*_m);
            }
            else{
                throw out_of_range("Matrix::operator/");
            }
        }

        T& operator()(int i, int j) const {
            if (i>= 0 && j>=0 && _n>i && _m>j)
                return _data[i][j];
            else
                throw out_of_range("Matrix::operator()");
        }

        Matrix<bool> operator&&(Matrix<T> const& b){
            if (_n ==b._n && _m==b._m){
                bool* result = new bool[_n*_m];
                for(int i = 0; i<_n; i++)
                    for (int j=0;j<_m;j++){
                        result[i*_n+j] = _data[i][j] && b._data[i][j];
                    }
                return Matrix<bool>(_n, _m, result, _n*_m);
            }
            else{
                throw out_of_range("Matrix::operator&&");
            }
        }

        Matrix<bool> operator||(Matrix<T> const& b){
            if (_n ==b._n && _m==b._m){
                bool* result = new bool[_n*_m];
                for(int i = 0; i<_n; i++)
                    for (int j=0;j<_m;j++){
                        result[i*_n+j] = _data[i][j] || b._data[i][j];
                    }
                Matrix<bool> s = Matrix<bool>(_n, _m, result, _n*_m);    
                return s;
            }
            else{
                throw out_of_range("Matrix::operator&&");
            }
        }
        Matrix<bool> operator !(){
            bool* result = new bool[_n*_m];
            for(int i = 0; i<_n; i++)
                for (int j=0;j<_m;j++){
                    result[i*_n+j] = !_data[i][j];
                }
            return Matrix<bool>(_n, _m, result, _n*_m);
        }  
        

        MaskedMatrix<T> operator()(Matrix<bool> const& mask){
            return MaskedMatrix<T>(*this, mask);       
            
        }
        int getSizeX() const {
            return _n;
        }
        int getSizeY() const {
            return _m;
        }

        const void printMatrix()
        {
            for(int i = 0; i<_n; i++){
                    for (int j=0;j<_m;j++){
                        cout << _data[i][j] << " ";
                    }
                cout << endl;    
            }
            cout << endl << endl;
        }
         
};

template<typename T>
const bool operator==(Matrix<T> const m1, Matrix<T> const m2){
            if (m2.getSizeX() == m1.getSizeX() && m2.getSizeY() == m1.getSizeY()){
                for(int i = 0; i<m1.getSizeX(); i++)
                    for (int j=0;j<m1.getSizeY();j++)
                        if (m2(i, j) != m1(i, j))
                            return false;
                return true;
            }
            return false;
        }

template <typename T>
class MaskedMatrix{
    template <typename U>
    friend const bool operator==(MaskedMatrix<U> const m1, MaskedMatrix<U> const m2);
     private:
        
        
    public:
    Matrix<T>& _matrix;
        const Matrix<bool>& _mask;
    
        MaskedMatrix<T>(Matrix<T> &m, const Matrix<bool> & mask): _matrix(m), _mask(mask) { 
            if (m.getSizeX() != mask.getSizeX() || m.getSizeY() != mask.getSizeY())
                throw out_of_range("MaskedMatrix::constructor");
        }

        void operator=(const T v){
            for (int i = 0; i<_mask.getSizeX(); ++i) 
		        for (int j = 0; j< _mask.getSizeY(); ++j) {
			        if (_mask._data[i][j] == true)
                        _matrix._data[i][j] = v;
			    }
	    }
};

template<typename T>
const bool operator==(MaskedMatrix<T> const m1, MaskedMatrix<T> const m2){
            if (m1._mask == m2._mask && m1._matrix == m2._matrix){
                return true;
            }
            return false;
        }