#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Search for a target value in a sorted array using exponential search.
 *
 * This algorithm grows the right boundary exponentially (1, 2, 4, 8, ...) to
 * find a containing range, then finishes with binary search in that range.
 * Useful when target is likely near the beginning or the array is unbounded.
 *
 * @tparam T The type of elements in the vector (must be comparable).
 * @param arr The sorted vector of elements to search.
 * @param target The value to search for.
 * @return The index of the target if found, nullopt otherwise.
 *
 * @note Time complexity: O(log p) where p is the position of the target
 * @note Space complexity: O(1)
 * @note The array must be sorted in ascending order.
 */
template <typename T>
std::optional<size_t> exponential_search(const vector<T> &arr, const T &target);

template <typename T>
std::optional<size_t> exponential_search(const vector<T> &arr, const T &target) {
  size_t n = arr.size();
  if (n == 0) {
    return std::nullopt;
  }

  // Check if target is at the first position
  if (arr[0] == target) {
    return 0;
  }

  // Find range for binary search by repeated doubling
  size_t bound = 1;
  while (bound < n && arr[bound] <= target) {
    bound *= 2;
  }

  // Binary search in the found range
  size_t low = bound / 2;
  size_t high = min(bound, n - 1);

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
template std::optional<size_t> exponential_search<int>(const vector<int> &arr, const int &target);
template std::optional<size_t> exponential_search<float>(const vector<float> &arr, const float &target);
template std::optional<size_t> exponential_search<double>(const vector<double> &arr, const double &target);
template std::optional<size_t> exponential_search<char>(const vector<char> &arr, const char &target);
