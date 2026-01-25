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
 * Return the values of the nodes visible from the right side of a binary tree.
 * 
 * @param root Root of the binary tree
 * @return Vector of node values visible from the right side, from top to bottom
 */
std::vector<int> rightSideView(TreeNode* root);


// Implementation

std::vector<int> rightSideView(TreeNode* root) {
    std::vector<int> result;
    
    if (root == nullptr) {
        return result;
    }
    
    std::queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = static_cast<int>(q.size());
        
        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = q.front();
            q.pop();
            
            // If this is the last node in this level, it's visible from right
            if (i == levelSize - 1) {
                result.push_back(node->val);
            }
            
            // Add children (left first, then right)
            if (node->left) {
                q.push(node->left);
            }
            if (node->right) {
                q.push(node->right);
            }
        }
    }
    
    return result;
}

