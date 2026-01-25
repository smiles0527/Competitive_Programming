#include <bits/stdc++.h>

using namespace std;

#pragma once

#include <vector>

/**
 * TreeNode for BST representation.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int v = 0) : val(v), left(nullptr), right(nullptr) {}
};

/**
 * Node for doubly linked list.
 */
struct ListNode {
    int val;
    ListNode* prev;
    ListNode* next;
    
    ListNode(int v = 0) : val(v), prev(nullptr), next(nullptr) {}
};

/**
 * Convert a BST to a sorted doubly linked list in-place.
 * The conversion is done in-order (left-root-right).
 * 
 * @param root Root of the BST
 * @return Head of the doubly linked list
 */
ListNode* bstToDoublyLinkedList(TreeNode* root);

/**
 * Helper to get all values in order from the linked list.
 * @param head Head of the linked list
 * @return Vector of values in order
 */
std::vector<int> listToVector(ListNode* head);


// Implementation

ListNode* bstToDoublyLinkedList(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }
    
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    
    // In-order traversal using stack
    std::stack<TreeNode*> stack;
    TreeNode* current = root;
    
    while (current != nullptr || !stack.empty()) {
        // Go to leftmost node
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }
        
        // Process node
        current = stack.top();
        stack.pop();
        
        // Create list node
        ListNode* node = new ListNode(current->val);
        
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        
        // Move to right subtree
        current = current->right;
    }
    
    return head;
}

std::vector<int> listToVector(ListNode* head) {
    std::vector<int> result;
    while (head != nullptr) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

