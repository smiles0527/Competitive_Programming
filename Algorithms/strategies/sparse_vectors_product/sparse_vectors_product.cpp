#include <bits/stdc++.h>

using namespace std;

#pragma once

#include <unordered_map>
#include <vector>

/**
 * Calculate the dot product of two sparse vectors.
 * Sparse vectors are represented as maps from index to value.
 * 
 * @param vec1 First sparse vector
 * @param vec2 Second sparse vector
 * @return Dot product of the two vectors
 */
int sparseVectorProduct(const std::unordered_map<int, int>& vec1,
                        const std::unordered_map<int, int>& vec2);

/**
 * Sparse vector class for efficient storage and dot product.
 */
class SparseVector {
public:
    /**
     * Create a sparse vector from a dense vector.
     * @param nums Dense vector representation
     */
    explicit SparseVector(const std::vector<int>& nums);
    
    /**
     * Calculate dot product with another sparse vector.
     * @param other Other sparse vector
     * @return Dot product
     */
    int dotProduct(const SparseVector& other) const;
    
private:
    std::unordered_map<int, int> data_;
};


// Implementation

int sparseVectorProduct(const std::unordered_map<int, int>& vec1,
                        const std::unordered_map<int, int>& vec2) {
    int result = 0;
    
    // Iterate over the smaller map for efficiency
    const auto& smaller = (vec1.size() <= vec2.size()) ? vec1 : vec2;
    const auto& larger = (vec1.size() <= vec2.size()) ? vec2 : vec1;
    
    for (const auto& pair : smaller) {
        auto it = larger.find(pair.first);
        if (it != larger.end()) {
            result += pair.second * it->second;
        }
    }
    
    return result;
}

SparseVector::SparseVector(const std::vector<int>& nums) {
    for (size_t i = 0; i < nums.size(); ++i) {
        if (nums[i] != 0) {
            data_[static_cast<int>(i)] = nums[i];
        }
    }
}

int SparseVector::dotProduct(const SparseVector& other) const {
    return sparseVectorProduct(data_, other.data_);
}

