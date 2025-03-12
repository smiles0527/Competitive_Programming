#include <bits/stdc++.h>
using namespace std;
 

const int INF = 1e8;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int N, M;
    cin >> N >> M;
    
    
    vector<vector<bool>> G(N, vector<bool>(N, false));
    vector<int> adj(N, 0);
    for (int i = 0; i < M; i++){
        int u, v;
        cin >> u >> v;
        u--; v--;
        G[u][v] = G[v][u] = true;
        adj[u] |= (1 << v);
        adj[v] |= (1 << u);
    }
 
    int totalStates = 1 << N;
    
    
    vector<int> ep(totalStates, 0), dp(totalStates, INF);
 
    
    
    for (int mask = 0; mask < totalStates; mask++){
        int cnt = 0;
        for (int i = 0; i < N; i++){
            if(mask & (1 << i)){
                for (int j = i+1; j < N; j++){
                    if(mask & (1 << j)){
                        if(G[i][j]) cnt++;
                    }
                }
            }
        }
        ep[mask] = cnt;
    }
 
    
    
    for (int mask = 0; mask < totalStates; mask++){
        int pc = __builtin_popcount(mask);
        if(pc <= 1){
            dp[mask] = INF;
        } else if(pc == 2){
            
            int u = -1, v = -1;
            for (int i = 0; i < N; i++){
                if(mask & (1 << i)){
                    if(u == -1) u = i; else v = i;
                }
            }
            
            dp[mask] = (G[u][v] ? 0 : 1);
        }
    }
 
    
    vector<int> order(totalStates);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b){
        return __builtin_popcount(a) < __builtin_popcount(b);
    });
 
    
    for (int mask : order) {
        int pc = __builtin_popcount(mask);
        if(pc < 3) continue; 
 
        
        
        
        
        
        
        
 
        
        int smallest = __builtin_ctz(mask);
        
        for (int sub = (mask - 1) & mask; sub; sub = (sub - 1) & mask) {
            if(sub == mask) continue;
            if(!(sub & (1 << smallest))) continue;
            int A = sub, B = mask ^ A;
            
            
            for (int stateA = 0; stateA < 2; stateA++){
                int costA = (stateA == 0 ? dp[A] : ep[A]);
                if(costA >= INF) continue;
                for (int stateB = 0; stateB < 2; stateB++){
                    int costB = (stateB == 0 ? dp[B] : ep[B]);
                    if(costB >= INF) continue;
                    int crossCost = 0;
                    
                    int temp = A;
                    while(temp){
                        int a = __builtin_ctz(temp);
                        temp &= temp - 1;
                        
                        int neigh = adj[a] & mask;
                        int missing = B & (~neigh);
                        crossCost += __builtin_popcount(missing);
                    }
                    dp[mask] = min(dp[mask], costA + costB + crossCost);
                }
            }
        }
    }
 
    
    
    int full = (1 << N) - 1;
    int bestNonEmpty = dp[full];
    int bestEmpty = ep[full]; 
    int finalCost = min(bestNonEmpty, bestEmpty);
    
    cout << finalCost << "\n";
    return 0;
}
