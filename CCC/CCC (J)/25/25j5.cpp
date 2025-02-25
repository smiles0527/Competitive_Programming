#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int R, C, M;
    cin >> R >> C >> M;
    vector<int> prev(C), cur(C);
    for (int j = 0; j < C; j++){
        prev[j] = (j % M) + 1;
    }
    for (int i = 1; i < R; i++){
        for (int j = 0; j < C; j++){
            int cost = (((long long)i * C + j) % M) + 1;
            int mn = prev[j];
            if(j > 0) mn = min(mn, prev[j-1]);
            if(j < C - 1) mn = min(mn, prev[j+1]);
            cur[j] = cost + mn;
        }
        prev.swap(cur);
    }
    int ans = prev[0];
    for (int j = 1; j < C; j++){
        ans = min(ans, prev[j]);
    }
    cout << ans;
    return 0;
}
