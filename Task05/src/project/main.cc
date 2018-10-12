#include <iostream>     // std::cout
#include <iterator>     // std::ostream_iterator
#include <vector>       // std::vector
#include <algorithm>    // std::copy
#include<MyIterator.h>
#include<MergeSort.h>

int main () {
  std::vector<int> myvector;
  // for (int i=10; i>1; --i) myvector.push_back(i*10);
//   for (int i=1; i<10; ++i) myvector.push_back(i*10);
  myvector.push_back(0);
  myvector.push_back(0);
  my_ostream_iterator<int> out_it (std::cout,", ", 1);
  std::copy ( myvector.begin(), myvector.end(), out_it );

  merge_sort(myvector.begin(), myvector.end(), &my_compare);  
  cout<<endl;
  
  // my_ostream_iterator<int> out_it (std::cout,", ", 1);
  std::copy ( myvector.begin(), myvector.end(), out_it );
  return 0;
}