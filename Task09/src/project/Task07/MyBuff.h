#include<streambuf>
#include<string>
#include<iostream>

class LineNumberBuffer : public std::streambuf
{
    std::streambuf* old;
    std::string str;
    std::string res;
    bool f=true;
    int N = 0;
    public:
        explicit LineNumberBuffer(std::streambuf* b): old(b) {}
    protected:
        int_type overflow(int_type c) override {
            if (f){
                str = std::to_string(N)+" ";
                old->sputn(str.data(), str.size());
                f = false;
                N++;
            }
            if (c == '\n') 
                f = true;
            return old->sputc(c);    
        }
 
        std::streamsize xsputn(const char* s, std::streamsize n) override {
            str.assign(s, n);
            if (N == 0){
                res = "0 ";
                N++;
            }
            else
                res = "";        
            for (char& ch : str){
                res += ch;
                if (ch == '\n'){
                    res += std::to_string(N)+" ";
                    res += " ";
                    N++;
                }
            }
            return old->sputn(res.data(), res.size());        
        }
};