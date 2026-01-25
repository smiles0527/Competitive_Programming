#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Search for a target value in an array using linear search.
 *
 * This algorithm scans the array from left to right, comparing each element
 * with the target until a match is found or the end is reached.
 *
 * @tparam T The type of elements in the vector (must be equality comparable).
 * @param arr The vector of elements to search.
 * @param target The value to search for.
 * @return The index of the target if found, nullopt otherwise.
 *
 * @note Time complexity: O(n)
 * @note Space complexity: O(1)
 */
template <typename T>
std::optional<size_t> linear_search(const vector<T> &arr, const T &target);

template <typename T>
std::optional<size_t> linear_search(const vector<T> &arr, const T &target) {
  for (size_t i = 0; i < arr.size(); ++i) {
    if (arr[i] == target) {
      return i;
    }
  }
return std::nullopt;
}

// Explicit template instantiations
template std::optional<size_t> linear_search<int>(const vector<int> &arr, const int &target);
template std::optional<size_t> linear_search<float>(const vector<float> &arr, const float &target);
template std::optional<size_t> linear_search<double>(const vector<double> &arr, const double &target);
template std::optional<size_t> linear_search<char>(const vector<char> &arr, const char &target);
