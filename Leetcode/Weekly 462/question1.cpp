#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
        vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k) {
            for (int i = 0; i < k / 2; ++i) {
                for (int j = 0; j < k; ++j) {
                    swap(grid[x + i][y + j], grid[x + k - 1 - i][y + j]);
                }
            }
            return grid;
        }
    };
    
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    cout << sol.add(3, 4) << "\n"; 
    return 0;
}
