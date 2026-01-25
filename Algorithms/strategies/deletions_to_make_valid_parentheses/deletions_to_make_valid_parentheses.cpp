#include <bits/stdc++.h>

using namespace std;

#pragma once

#include <string>

/**
 * Determine the minimum number of deletions needed to make a string of parentheses valid.
 * A string of parentheses is valid if each opening parenthesis has a matching closing parenthesis.
 * 
 * @param s String containing parentheses
 * @return Minimum number of deletions needed
 */
int minDeletionsToMakeValid(const std::string& s);


// Implementation

int minDeletionsToMakeValid(const std::string& s) {
    int openCount = 0;   // Unmatched opening parentheses
    int deletions = 0;   // Required deletions
    
    for (char c : s) {
        if (c == '(') {
            openCount++;
        } else if (c == ')') {
            if (openCount > 0) {
                // Matched with an opening parenthesis
                openCount--;
            } else {
                // No matching opening parenthesis, must delete this
                deletions++;
            }
        }
    }
    
    // Any remaining unmatched opening parentheses must be deleted
    return deletions + openCount;
}

