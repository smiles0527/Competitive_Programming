// Selection Sort
// Time: O(n²) all cases
// Space: O(1)

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

template <typename T>
void selection_sort(vector<T> &arr) {
  for (auto it = begin(arr); it != end(arr); ++it) {
    auto const min_elem = min_element(it, end(arr));
    iter_swap(min_elem, it);
  }
}

// Explicit template instantiations
template void selection_sort<int>(vector<int> &arr);
template void selection_sort<float>(vector<float> &arr);
template void selection_sort<double>(vector<double> &arr);
template void selection_sort<char>(vector<char> &arr);
