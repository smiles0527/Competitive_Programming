#include <bits/stdc++.h>

using namespace std;

#pragma once

#include <vector>

/**
 * Calculate the sum of all elements in a subarray.
 * 
 * @param arr Input array
 * @param start Start index (inclusive)
 * @param end End index (inclusive)
 * @return Sum of elements from start to end
 */
int subarraySum(const std::vector<int>& arr, int start, int end);

/**
 * Prefix sum array for efficient range sum queries.
 * Supports O(1) range queries after O(n) preprocessing.
 */
class PrefixSum {
public:
    /**
     * Build prefix sum array from input.
     * @param arr Input array
     */
    explicit PrefixSum(const std::vector<int>& arr);
    
    /**
     * Get sum of elements from start to end (inclusive).
     * @param start Start index
     * @param end End index
     * @return Sum of elements in range
     */
    int rangeSum(int start, int end) const;
    
private:
    std::vector<long long> prefix_;
};


// Implementation

int subarraySum(const std::vector<int>& arr, int start, int end) {
    if (arr.empty() || start < 0 || end >= static_cast<int>(arr.size()) || start > end) {
        return 0;
    }
    
    int sum = 0;
    for (int i = start; i <= end; ++i) {
        sum += arr[i];
    }
    return sum;
}

PrefixSum::PrefixSum(const std::vector<int>& arr) {
    prefix_.resize(arr.size() + 1, 0);
    for (size_t i = 0; i < arr.size(); ++i) {
        prefix_[i + 1] = prefix_[i] + arr[i];
    }
}

int PrefixSum::rangeSum(int start, int end) const {
    if (start < 0 || end >= static_cast<int>(prefix_.size()) - 1 || start > end) {
        return 0;
    }
    return static_cast<int>(prefix_[end + 1] - prefix_[start]);
}

