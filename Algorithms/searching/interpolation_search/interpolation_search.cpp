#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Search for a target value in a sorted array using interpolation search.
 *
 * This algorithm estimates the likely position of the target using the values
 * themselves, then probes there and narrows the search based on comparison.
 * Works best on uniformly distributed sorted data.
 *
 * @param arr The sorted vector of integers to search.
 * @param target The value to search for.
 * @return The index of the target if found, nullopt otherwise.
 *
 * @note Time complexity: O(log log n) average for uniform data, O(n) worst case
 * @note Space complexity: O(1)
 * @note The array must be sorted in ascending order.
 */
optional<size_t> interpolation_search(const vector<int> &arr, int target);

optional<size_t> interpolation_search(const vector<int> &arr, int target) {
  if (arr.empty()) {
    return nullopt;
  }

  size_t low = 0;
  size_t high = arr.size() - 1;

  while (low <= high && target >= arr[low] && target <= arr[high]) {
    // Handle case where all elements are the same
    if (arr[high] == arr[low]) {
      if (arr[low] == target) {
        return low;
      }
      return nullopt;
    }

    // Estimate position using interpolation formula
    size_t pos = low + static_cast<size_t>(
        (static_cast<double>(target - arr[low]) / (arr[high] - arr[low])) * (high - low)
    );

    // Ensure pos is within bounds
    pos = max(low, min(pos, high));

    if (arr[pos] == target) {
      return pos;
    } else if (arr[pos] < target) {
      low = pos + 1;
    } else {
      if (pos == 0) {
        break;
      }
      high = pos - 1;
    }
  }

  return nullopt;
}
