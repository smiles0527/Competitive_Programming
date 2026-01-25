// Insertion Sort
// Time: O(n²) worst/average, O(n) best (already sorted)
// Space: O(1)

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

template <typename T>
void insertion_sort(vector<T> &arr) {
  for (auto it = begin(arr); it != end(arr); ++it) {
    rotate(upper_bound(begin(arr), it, *it), it, next(it));
  }
}

// Explicit template instantiations
template void insertion_sort<int>(vector<int> &arr);
template void insertion_sort<float>(vector<float> &arr);
template void insertion_sort<double>(vector<double> &arr);
template void insertion_sort<char>(vector<char> &arr);
