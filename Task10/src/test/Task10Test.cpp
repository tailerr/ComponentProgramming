#include <gtest/gtest.h>
#include <project/vec_transpose.h>

TEST(Rotate, _){

    std::vector<int> v({1, 2});
    std::vector<int> v1({-2, 1});
    std::vector<int> v2({-1, -2});
    std::vector<int> v3({2, -1});
    
    
    for (int i=0;i<2;i++){
        EXPECT_EQ(rotate(v, i*360+90), v1);
        EXPECT_EQ(rotate(v, i*360+180), v2);
        EXPECT_EQ(rotate(v, i*360+270), v3);
        EXPECT_EQ(rotate(v, i*360+360), v);
    }
    EXPECT_THROW(rotate(v, 30), std::invalid_argument);
}
