#include <gtest/gtest.h>
#include <project/User.h>

TEST(Trait, _){

    std::unordered_set<Person> members;
    Person p = Person("Alice", "S", 1);
    members.insert(p);
    members.insert(Person("Alex", "P", 2));
    Trait<Person> tr;

    Group g = Group("name", 1, 2, members);
    Trait<Group> tr1;

    EXPECT_EQ(9,  tr.size(p));
    EXPECT_EQ(31, tr1.size(g));

}