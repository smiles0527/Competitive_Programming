#include <bits/stdc++.h>

using namespace std;

#pragma once

#include <string>

/**
 * Determine whether a given string can be made into a palindrome by deleting at most one character.
 * 
 * @param s Input string
 * @return True if the string is already a palindrome or can become one by deleting one character
 */
bool isPalindromeAfterDeletion(const std::string& s);


// Implementation

// Helper function to check if substring is palindrome
static bool isPalindrome(const std::string& s, int left, int right) {
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

bool isPalindromeAfterDeletion(const std::string& s) {
    int left = 0;
    int right = static_cast<int>(s.length()) - 1;
    
    while (left < right) {
        if (s[left] != s[right]) {
            // Try deleting either the left or right character
            return isPalindrome(s, left + 1, right) || 
                   isPalindrome(s, left, right - 1);
        }
        left++;
        right--;
    }
    
    // Already a palindrome
    return true;
}

