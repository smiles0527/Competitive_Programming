// Quick Sort
// Time: O(n log n) average, O(n²) worst
// Space: O(log n) recursion stack

#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

namespace {

template <typename T>
void quick_sort_impl(vector<T> &arr, size_t start, size_t end) {
  while (end > start) {
    size_t i = start;
    size_t j = end;

    while (i < j) {
      while (arr[i] < arr[start] && i < j) {
        ++i;
      }
      --j;
      while (j > start && arr[j] > arr[start]) {
        --j;
      }
      if (i < j) {
        swap(arr[i], arr[j]);
      }
    }
    swap(arr[start], arr[j]);

    // Tail-call optimization: recurse on smaller partition
    if (j - start > end - (j + 1)) {
      quick_sort_impl(arr, start, j);
      start = j + 1;
    } else {
      if (j + 1 < end) {
        quick_sort_impl(arr, j + 1, end);
      }
      end = j;
    }
  }
}

} // namespace

template <typename T>
void quick_sort(vector<T> &arr) {
  if (!arr.empty()) {
    quick_sort_impl(arr, 0, arr.size());
  }
}

// Explicit template instantiations
template void quick_sort<int>(vector<int> &arr);
template void quick_sort<float>(vector<float> &arr);
template void quick_sort<double>(vector<double> &arr);
template void quick_sort<char>(vector<char> &arr);
