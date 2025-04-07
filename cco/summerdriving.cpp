#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
#include <functions>
#include <algorithm>
using namespace std;
 
int N, R, A, B;
vector<vector<int>> adj;
unordered_map<long long,int> dp;
 
int finalPhase(int v, int p) {
    int ans = v;
    queue<pair<int,int>> q;
    q.push({v, 0});
    vector<bool> visited(N+1, false);
    visited[v] = true;
    while(!q.empty()){
        auto cur = q.front();
        q.pop();
        ans = min(ans, cur.first);
        int d = cur.second;
        if(d == B) continue;
        for (int nxt : adj[cur.first]){
            if(nxt == p) continue;
            if(!visited[nxt]){
                visited[nxt] = true;
                q.push({nxt, d+1});
            }
        }
    }
    return ans;
}
 
int solveState(int v, int p);
 
int enumeratePaths(int v, int p) {
    int bestOutcome = -1;
    vector<int> path(A+1);
    vector<int> idx(A+1, 0);
    int depth = 0;
    path[0] = v;
    while(depth >= 0){
        if(depth == A){
            int currentOutcome = INT_MAX;
            int startIndex = max(0, A - B);
            for (int j = startIndex; j <= A; j++){
                int newv = path[j];
                int newp = (j == 0 ? -1 : path[j-1]);
                int outcome = solveState(newv, newp);
                currentOutcome = min(currentOutcome, outcome);
            }
            bestOutcome = max(bestOutcome, currentOutcome);
            depth--;
            continue;
        }
        int cur = path[depth];
        int par = (depth == 0 ? p : path[depth-1]);
        if(idx[depth] < (int)adj[cur].size()){
            int nxt = adj[cur][idx[depth]++];
            if(nxt == par) continue;
            path[depth+1] = nxt;
            idx[depth+1] = 0;
            depth++;
            continue;
        } else {
            idx[depth] = 0;
            depth--;
        }
    }
    return bestOutcome;
}
 
int solveState(int v, int p) {
    long long key = ((long long)v << 32) | (unsigned int)(p+1);
    if(dp.find(key) != dp.end()) return dp[key];
    int outcome = enumeratePaths(v, p);
    if(outcome == -1)
        outcome = finalPhase(v, p);
    dp[key] = outcome;
    return outcome;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> R >> A >> B;
    adj.resize(N+1);
    for (int i = 1; i <= N-1; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cout << solveState(R, -1) << "\n";
    return 0;
}
