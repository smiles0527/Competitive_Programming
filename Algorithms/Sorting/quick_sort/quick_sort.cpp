// Quick Sort
// Time: O(n log n) average, O(n²) worst
// Space: O(log n) recursion stack

#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

namespace {

template <typename T>
void quick_sort_impl(std::vector<T> &arr, std::size_t start, std::size_t end) {
  while (end > start) {
    std::size_t i = start;
    std::size_t j = end;

    while (i < j) {
      while (arr[i] < arr[start] && i < j) {
        ++i;
      }
      --j;
      while (j > start && arr[j] > arr[start]) {
        --j;
      }
      if (i < j) {
        std::swap(arr[i], arr[j]);
      }
    }
    std::swap(arr[start], arr[j]);

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
void quick_sort(std::vector<T> &arr) {
  if (!arr.empty()) {
    quick_sort_impl(arr, 0, arr.size());
  }
}

// Explicit template instantiations
template void quick_sort<int>(std::vector<int> &arr);
template void quick_sort<float>(std::vector<float> &arr);
template void quick_sort<double>(std::vector<double> &arr);
template void quick_sort<char>(std::vector<char> &arr);
