#include <iterator>

using namespace std;

template <typename T, typename charT=char,
        typename traits = char_traits<charT>>
class my_ostream_iterator: 
 public iterator<output_iterator_tag, void, void, void, void>
 {
     basic_ostream<charT, traits>* out_stream;
     const charT* delim;
     private:
        int N;
        int k;
     public:
        typedef charT char_type;
        typedef traits traits_type;
        typedef basic_ostream<charT,traits> ostream_type;

        my_ostream_iterator(ostream_type& s, int n) : out_stream(&s), delim(0), N(n), k(n) {}

        my_ostream_iterator(ostream_type& s, const charT* delimiter, int n)
            : out_stream(&s), delim(delimiter), N(n), k(n) { }

        my_ostream_iterator(const my_ostream_iterator<T,charT,traits>& x)
            : out_stream(x.out_stream), delim(x.delim), N(x.N), k(x.N) {}    

        ~my_ostream_iterator() {}
        my_ostream_iterator<T,charT,traits>& operator*() { return *this; }
        my_ostream_iterator<T,charT,traits>& operator++() { return *this; }
        my_ostream_iterator<T,charT,traits>& operator++(int) { return *this; }

        my_ostream_iterator<T,charT,traits>& operator= (const T& value) {
            if (N == k){
                *out_stream << value;
                if (delim!=0) *out_stream << delim;
                k = 1;
            }
            else{
                k++;
            }
            return *this;
        }

 };
