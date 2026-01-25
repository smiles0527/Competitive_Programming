#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Search for a target value in a sorted array using jump search.
 *
 * This algorithm jumps ahead by fixed block sizes to find the block that may
 * contain the target, then performs a linear scan inside that block.
 *
 * @tparam T The type of elements in the vector (must be comparable).
 * @param arr The sorted vector of elements to search.
 * @param target The value to search for.
 * @return The index of the target if found, nullopt otherwise.
 *
 * @note Time complexity: O(√n)
 * @note Space complexity: O(1)
 * @note The array must be sorted in ascending order.
 */
template <typename T>
optional<size_t> jump_search(const vector<T> &arr, const T &target);

template <typename T>
optional<size_t> jump_search(const vector<T> &arr, const T &target) {
  size_t n = arr.size();
  if (n == 0) {
    return nullopt;
  }

  size_t step = static_cast<size_t>(sqrt(static_cast<double>(n)));
  size_t prev = 0;

  // Jump ahead until we find a block where target could be
  while (arr[min(step, n) - 1] < target) {
    prev = step;
    step += static_cast<size_t>(sqrt(static_cast<double>(n)));
    if (prev >= n) {
      return nullopt;
    }
  }

  // Linear search within the block
  while (arr[prev] < target) {
    ++prev;
    if (prev == min(step, n)) {
      return nullopt;
    }
  }

  if (arr[prev] == target) {
    return prev;
  }

  return nullopt;
}

// Explicit template instantiations
template optional<size_t> jump_search<int>(const vector<int> &arr, const int &target);
template optional<size_t> jump_search<float>(const vector<float> &arr, const float &target);
template optional<size_t> jump_search<double>(const vector<double> &arr, const double &target);
template optional<size_t> jump_search<char>(const vector<char> &arr, const char &target);
