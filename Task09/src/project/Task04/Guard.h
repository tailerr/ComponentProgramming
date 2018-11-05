#include <ostream>

using namespace std;

class MyGuard{
    private:
        ostream& stream;
        ios_base::fmtflags flags;
        char fill;
    MyGuard(ostream s): stream(s), flags(s.flags()), fill(s.fill()){}
    ~MyGuard(){
        stream.flags(flags);
        stream.fill(fill);
    }
};