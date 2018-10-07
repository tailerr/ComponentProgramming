#include <gtest/gtest.h>
#include <project/Matrix.h>

template <typename T>
struct params
{
    Matrix<T> input;
    Matrix<T> expected_output;
};

Matrix<int> example = Matrix<int>(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}, 9);
Matrix<bool> bExample = Matrix<bool>(3, 3, {1,1,1,1,1,1,1,1,1}, 9);

class matrixInt_test : public ::testing::TestWithParam<params<int>>
{
};
class matrixBool_test : public ::testing::TestWithParam<params<bool>>
{
};

TEST_P(matrixInt_test, _)
{
    const params<int> &param = GetParam();

    EXPECT_EQ(param.expected_output, param.input);
}

INSTANTIATE_TEST_CASE_P(
    _,
    matrixInt_test,
    ::testing::Values(
        params<int>{
            example + example,
            Matrix<int>(3, 3, {2, 4, 6, 8, 10, 12, 14, 16, 18}, 9)},
        params<int>{
            example * example,
            Matrix<int>(3, 3, {1, 4, 9, 16, 25, 36, 49, 64, 81}, 9)},
        params<int>{
            Matrix<int>(3, 3, {1, 4, 9, 16, 25, 36, 49, 64, 81}, 9) / example,
            example},
        params<int>{
            Matrix<int>(3, 3, {2, 4, 6, 8, 10, 12, 14, 16, 18}, 9) - example,
            example}));

TEST_P(matrixBool_test, _)
{
    const params<bool> &param = GetParam();

    EXPECT_EQ(param.expected_output, param.input);
}

INSTANTIATE_TEST_CASE_P(
    _,
    matrixBool_test,
    ::testing::Values(
        params<bool>{
            Matrix<bool>(3, 3, {0, 1, 1, 1, 1, 1, 1, 1, 1}, 9) && bExample,
            Matrix<bool>(3, 3, {0, 1, 1, 1, 1, 1, 1, 1, 1}, 9)},
        params<bool>{
            Matrix<bool>(3, 3, {0, 1, 1, 1, 1, 1, 1, 1, 1}, 9) || Matrix<bool>(3, 3, {0, 1, 1, 1, 1, 1, 1, 1, 1}, 9),
            Matrix<bool>(3, 3, {0, 1, 1, 1, 1, 1, 1, 1, 1}, 9)},
        params<bool>{
            !Matrix<bool>(3, 3, {1, 0, 0, 0, 0, 0, 0, 0, 0}, 9),
             Matrix<bool>(3, 3, {0, 1, 1, 1, 1, 1, 1, 1, 1}, 9)}));

template <typename T>
struct mParams
{
    MaskedMatrix<T> input;
    MaskedMatrix<T> expected_output;
};

class maskedMatrix_test : public ::testing::TestWithParam<mParams<int>>
{
};

TEST_P(maskedMatrix_test, _)
{
    const mParams<int> &param = GetParam();

    EXPECT_EQ(param.expected_output, param.input);
}

INSTANTIATE_TEST_CASE_P(
    _,
    maskedMatrix_test,
    ::testing::Values(
        mParams<int>{
            MaskedMatrix<int>(example, bExample),
            example(bExample)
            }
            ));            