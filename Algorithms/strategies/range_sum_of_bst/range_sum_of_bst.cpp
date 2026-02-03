#include <bits/stdc++.h>

using namespace std;

#pragma once

#include <vector>

/**
 * TreeNode for binary tree representation.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int v = 0) : val(v), left(nullptr), right(nullptr) {}
    TreeNode(int v, TreeNode* l, TreeNode* r) : val(v), left(l), right(r) {}
};

/**
 * Calculate the sum of all nodes in a BST within the given range [low, high].
 * 
 * @param root Root of the BST
 * @param low Lower bound of range (inclusive)
 * @param high Upper bound of range (inclusive)
 * @return Sum of all nodes with values in [low, high]
 */
int rangeSumBST(TreeNode* root, int low, int high);


// Implementation

int rangeSumBST(TreeNode* root, int low, int high) {
    if (root == nullptr) {
        return 0;
    }
    
    int sum = 0;
    
    // If current value is in range, add it
    if (root->val >= low && root->val <= high) {
        sum += root->val;
    }
    
    // If current value > low, there might be values in left subtree
    if (root->val > low) {
        sum += rangeSumBST(root->left, low, high);
    }
    
    // If current value < high, there might be values in right subtree
    if (root->val < high) {
        sum += rangeSumBST(root->right, low, high);
    }
    
    return sum;
}

