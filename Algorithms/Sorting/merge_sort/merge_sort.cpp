// Merge Sort
// Time: O(n log n) all cases
// Space: O(n) for temporary arrays

#include <cstddef>
#include <iostream>
#include <vector>

namespace {

template <typename T>
void merge(std::vector<T> &arr, std::size_t start, std::size_t end) {
  std::size_t mid = (start + end) / 2;
  std::vector<T> temp(end - start + 1);

  std::size_t i = 0;
  std::size_t left = start;
  std::size_t right = mid + 1;

  while (left <= mid && right <= end) {
    if (arr[left] < arr[right]) {
      temp[i++] = arr[left++];
    } else {
      temp[i++] = arr[right++];
    }
  }

  while (left <= mid) {
    temp[i++] = arr[left++];
  }

  while (right <= end) {
    temp[i++] = arr[right++];
  }

  for (std::size_t j = start; j <= end; ++j) {
    arr[j] = temp[j - start];
  }
}

template <typename T>
void merge_sort_impl(std::vector<T> &arr, std::size_t start, std::size_t end) {
  if (start < end) {
    std::size_t mid = (start + end) / 2;
    merge_sort_impl(arr, start, mid);
    merge_sort_impl(arr, mid + 1, end);
    merge(arr, start, end);
  }
}

} // namespace

template <typename T>
void merge_sort(std::vector<T> &arr) {
  if (!arr.empty()) {
    merge_sort_impl(arr, 0, arr.size() - 1);
  }
}

// Explicit template instantiations
template void merge_sort<int>(std::vector<int> &arr);
template void merge_sort<float>(std::vector<float> &arr);
template void merge_sort<double>(std::vector<double> &arr);
template void merge_sort<char>(std::vector<char> &arr);
