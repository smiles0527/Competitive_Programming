#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, U;
    cin >> N >> U;
    int half = N / 2;
    
    vector<string> grid(N);
    for (int i = 0; i < N; i++){
        cin >> grid[i];
    }
    
    vector<vector<int>> groupCount(half, vector<int>(N, 0));
    vector<vector<int>> groupCost(half, vector<int>(N, 0));
    
    long long totalOps = 0;
    auto computeCost = [&](int count) -> int {
        return m    in(count, 4 - count);
    };
    
    for (int i = 0; i < half; i++){
        for (int j = half; j < N; j++){
            
            
            int cnt = 0;
            cnt += (grid[i][j] == '#');
            cnt += (grid[i][N-1-j] == '#');
            cnt += (grid[N-1-i][j] == '#');
            cnt += (grid[N-1-i][N-1-j] == '#');
            groupCount[i][j] = cnt;
            groupCost[i][j] = computeCost(cnt);
            totalOps += groupCost[i][j];
        }
    }
    cout << totalOps << "\n";
    for (int u = 0; u < U; u++){
        int r, c;
        cin >> r >> c;
        r--; c--;
        int gr = min(r, N - 1 - r);
        int gc = max(c, N - 1 - c);
         
        totalOps -= groupCost[gr][gc];
        char newVal;
        if(grid[r][c] == '#'){
            newVal = '.';
        } else {
            newVal = '#';
        }
        grid[r][c] = newVal;
        
        if(newVal == '#'){
            groupCount[gr][gc]++; 
        } else {
            groupCount[gr][gc]--;
        }
        
        groupCost[gr][gc] = computeCost(groupCount[gr][gc]);
        totalOps += groupCost[gr][gc];
        cout << totalOps << "\n";
    }
    return 0;
}
