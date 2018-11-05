#include <gtest/gtest.h>
#include <project/Task06/User.h>
TEST(Trait, _){

    std::unordered_set<Person> members;
    Person p = Person("Alice", "S", 1);
    members.insert(p);
    members.insert(Person("Alex", "P", 2));

    Group g = Group("name", 1, 2, members);

    EXPECT_EQ(10,  Trait<Person>::size(p));
    EXPECT_EQ(31, Trait<Group>::size(g));

}