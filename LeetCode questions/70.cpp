#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];

        /*
        Alternative solution using binet's formula

        double x = sqrt(5);
        double a = (1 + x) / 2;
        double b = (1 - x) / 2;

        return (int)((pow(a, n + 1) - pow(b, n + 1)) / x);
        */
    }
};

int main() {
    Solution sol;
    return 0;
}