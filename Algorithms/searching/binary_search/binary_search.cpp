#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Search for a target value in a sorted array using binary search.
 *
 * This algorithm repeatedly halves the search interval by comparing the
 * target to the middle element until found or the interval is empty.
 *
 * @tparam T The type of elements in the vector (must be comparable).
 * @param arr The sorted vector of elements to search.
 * @param target The value to search for.
 * @return The index of the target if found, nullopt otherwise.
 *
 * @note Time complexity: O(log n)
 * @note Space complexity: O(1)
 * @note The array must be sorted in ascending order.
 */
template <typename T>
std::optional<size_t> binary_search(const vector<T> &arr, const T &target);

template <typename T>
std::optional<size_t> binary_search(const vector<T> &arr, const T &target) {
  if (arr.empty()) {
    return std::nullopt;
  }

  size_t low = 0;
  size_t high = arr.size() - 1;

  while (low <= high) {
    size_t mid = low + (high - low) / 2;
    if (arr[mid] == target) {
      return mid;
    } else if (arr[mid] < target) {
      low = mid + 1;
    } else {
      if (mid == 0) {
        break;
      }
      high = mid - 1;
    }
  }

  return std::nullopt;
}

// Explicit template instantiations
template std::optional<size_t> binary_search<int>(const vector<int> &arr, const int &target);
template std::optional<size_t> binary_search<float>(const vector<float> &arr, const float &target);
template std::optional<size_t> binary_search<double>(const vector<double> &arr, const double &target);
template std::optional<size_t> binary_search<char>(const vector<char> &arr, const char &target);
