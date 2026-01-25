// Heap Sort
// Time: O(n log n) all cases
// Space: O(1)

#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

namespace {

template <typename T>
void heapify(vector<T> &arr, size_t curr, size_t offset) {
  auto parent = [](size_t i) { return i >> 1; };
  auto left_child = [](size_t i) { return i << 1; };
  auto right_child = [](size_t i) { return (i << 1) + 1; };

  if (curr + offset > arr.size()) {
    return;
  }

  heapify(arr, left_child(curr), offset);
  heapify(arr, right_child(curr), offset);

  if (curr > 1 && arr[curr + offset - 1] < arr[parent(curr) + offset - 1]) {
    swap(arr[curr + offset - 1], arr[parent(curr) + offset - 1]);
  }
}

} // namespace

template <typename T>
void heap_sort(vector<T> &arr) {
  for (size_t i = 0; i < arr.size(); ++i) {
    heapify(arr, 1, i);
  }
}

// Explicit template instantiations
template void heap_sort<int>(vector<int> &arr);
template void heap_sort<float>(vector<float> &arr);
template void heap_sort<double>(vector<double> &arr);
template void heap_sort<char>(vector<char> &arr);
