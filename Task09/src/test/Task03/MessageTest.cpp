#include <gtest/gtest.h>
#include <project/Task03/Message.h>


TEST(Message, runtime_error)
{
    stringstream f;
    try {
        message(f, "% + % = % % \n",'a', 1, 2.0);
        FAIL() << "Expected std::runtime_error";
    }
    catch(std::runtime_error const & err) {
        EXPECT_EQ(err.what(),std::string("неправильный формат строки: отсутствуют аргументы"));
    }
    catch(...) {
        FAIL() << "Expected std::runtime_error";
    }
}

TEST(Message_test, runtime_error)
{
    stringstream f;
    try {
        message(f, "% + % = \n",'a', 1, 2.0);
        FAIL() << "Expected std::runtime_error";
    }
    catch(std::runtime_error const & err) {
        EXPECT_EQ(err.what(), std::string("неправильный формат строки: много аргументов"));
    }
    catch(...) {
        FAIL() << "Expected std::runtime_error";
    }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}