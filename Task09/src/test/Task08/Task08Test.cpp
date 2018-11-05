#include <gtest/gtest.h>
#include "../project/Task08/MergeSort.h"
#include <algorithm>
#include <cstdlib>

TEST(ParallelMergeSort, _){
    std::vector<int> vec(10);
    std::generate(vec.begin(), vec.end(), std::rand);
    std::vector<int> vec1(vec);
    merge_sort(vec.begin(), vec.end(), my_compare);
    parallel_merge_sort(vec1.begin(), vec1.end(), my_compare);
    EXPECT_EQ(vec, vec1);
}