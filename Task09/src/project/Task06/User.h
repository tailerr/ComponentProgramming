#include<string>
#include<unordered_set>


class Person {
    public: 
        int ID;  
        std::string first_name;
        std::string last_name;
        Person(std::string fn, std::string ln, int id):
            ID(id), first_name(fn), last_name(ln) { }
        bool operator==(const Person & p) const {
            if (ID == p.ID){
                return true;
            }
            return false;
        }    
};

namespace std{
    template <class Iterator>
    struct hash;

    template<>
    struct hash<Person>{
        size_t operator()(const Person & x) const {
            return std::hash<int>()(x.ID);
        }
    };

    template <class Iterator>
    struct equal_to;

    template<>
    struct equal_to<Person>{
        bool operator()(const Person& x, const Person& y) const { return x==y; }
    };
}    

class Group{
    public:
        std::string name;
        int id;
        int N;
        std::unordered_set<Person> members;
        Group(std::string g_n, int ID, int n, const std::unordered_set<Person>& m):
            name(g_n), id(ID), N(n), members(m){ }
};

template<class T>
class Trait;

template<>
class Trait<Person>{
    public:
        static size_t size(const Person& p){
            return p.first_name.size() + p.last_name.size() + sizeof(p.ID);
    }
};

template<>
class Trait<Group>{
    public:
        static size_t size(Group& g){
            size_t res = g.name.size() + sizeof(g.id) + sizeof(g.N);
            Trait<Person> trait;
            for(auto k=g.members.begin(); k!=g.members.end();k++){
                res += trait.size(*k);
            }
            return res;
        }      
    
};



