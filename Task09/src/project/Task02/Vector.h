#include <iostream>

using namespace std;



template <typename T>
class Vector
{
  private:
    T *_data=nullptr;
    int _capacity;
    int _size;
    inline void reallocate();
  public:
    void push_back(T & elem);
    void push_back(T&& elem); 
    void pop_back();
    void swap(Vector<T>& t);
    Vector(T *_data, int n);
    Vector();
    ~Vector();
    Vector(const Vector<T> & v);
    Vector(Vector&& v);
    void printVector();
    int size();
    Vector<T>& operator=(Vector<T>&& v);
    Vector<T>&& operator=(const Vector<T> & v);
    T& operator[](int const& ind);
    using iterator = T*; 
    iterator begin() const{ return &_data[0]; }
    iterator end() const{ return &_data[_size]; }
    iterator erase(iterator ind1, iterator ind2){
        if (ind1< ind2 && ind1>=begin() && ind2<= end()){
            uint n = ind2-ind1;
            for (auto i=ind1; (i+n)<end();i++ ){
                *i = *(i+n);
            }
            this->_size -= n;
            if ((_size)*4 < _capacity){
                _capacity = int(_capacity/2);
                reallocate();
            }
            return ind1+1;
        }
        else{
            throw std::out_of_range("Vector::erase");
        }
    }
};

template <typename T>
inline void Vector<T>::reallocate() {
    T *arr = new T[_capacity];
    std::swap(arr, _data);
	//memmove(arr, _data, _size * sizeof(T));
    for (int i = 0; i < _size; i++){
        _data[i] = std::move(arr[i]);
    }
    if (arr != _data) delete[] arr;
}

template <typename T>
Vector<T>::Vector(){
    _capacity = 1;
    _size = 0;
}

// destructor
template <typename T>
Vector<T>::~Vector()
{
    delete [] _data;
}

// constructor with array
template <typename T>
Vector<T>::Vector(T *input, int n)
{
    _capacity = int(1.5 * n);
    _size = n;
    _data = new T* [_capacity];
    
    for (int i = 0; i < n; i++)
    {
        _data[i] = input[i];
    }
}

// constructor copy
template <typename T>
Vector<T>::Vector(const Vector<T> & v){
    _capacity = v._capacity;
    _size = v._size;
    _data = new T* [_capacity];
    
    for (int i = 0; i < _size; i++)
    {
        _data[i] = v._data[i];
    }
}

// constructor move
template <typename T>
Vector<T>::Vector(Vector<T>&& v){
    _data = v._data;
    _capacity = v._capacity;
    _size = v._size;
    v._size = 0;
    v._capacity = 0;
    v._data = nullptr;
}

template <typename T>
int Vector<T>::size(){
    return _size;
}

template <typename T>
void Vector<T>::push_back(T &elem)
{
    if (_size + 1 >= _capacity)
    {
        _capacity = 2 * _capacity;
        reallocate();
    }
    _data[_size] = elem;
    _size++;
}

template <typename T>
void Vector<T>::push_back(T&& elem){
    if (_size + 1 >= _capacity)
    {
        _capacity = 2 * _capacity;
        reallocate();
                
    }
    _data[_size] = move(elem);
    _size++;
}

template <typename T>
void Vector<T>::pop_back()
{
    _size--;
}

template <typename T>
void Vector<T>::swap(Vector<T>& t)
{
    std::swap(_data, t._data);
    std::swap(_size, t._size);
    std::swap(_capacity, t._capacity);
};

template <typename T>
void Vector<T>::printVector()
{
    for (int i = 0; i < _size; i++)
        cout << _data[i] << " ";
    cout<<endl;    
}

// with move
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& v){
    delete [] _data; 
    _capacity = v._capacity;
    _size = v._size;
    _data = v._data;
    v._data = nullptr;
    return *this;

}

// with copy
template <typename T>
Vector<T>&& Vector<T>::operator=(const Vector<T> & v){
    _capacity = v._capacity;
    _size = v._size;
    delete [] _data;
    _data = new T* [_capacity];
    for (int i = 0; i < _size; i++)
    {
        _data[i] = v._data[i];
    }
    return *this;
}

template <typename T>
T& Vector<T>::operator[](int const& ind){
    return _data[ind];
}

template <typename T>
void swap(Vector<T>& a, Vector<T>& b)
{
    a.swap(b);
}