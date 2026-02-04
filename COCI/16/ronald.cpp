#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;
    vector<vector<bool>> adj(N+1, vector<bool>(N+1,false));
    int a, b;
    for(int i = 0; i < M; i++){
        cin >> a >> b;
        adj[a][b] = adj[b][a] = true;
    }
    int u = 1;
    vector<int> group(N+1);
    group[u] = 0;
    for(int v = 1; v <= N; v++){
        if(v == u) continue;
        group[v] = adj[u][v] ? 0 : 1;
    }
    long long cnt0 = 0, cnt1 = 0;
    for(int i = 1; i <= N; i++){
        for(int j = i+1; j <= N; j++){
            if(adj[i][j]){
                if(group[i] != group[j]){
                    cout << "NE";
                    return 0;
                }
                if(group[i] == 0) cnt0++;
                else cnt1++;
            }
        }
    }
    long long s0 = 0, s1 = 0;
    for(int i = 1; i <= N; i++){
        if(group[i] == 0) s0++;
        else s1++;
    }
    if(cnt0 != s0*(s0-1LL)/2 || cnt1 != s1*(s1-1LL)/2)
        cout << "NE";
    else
        cout << "DA";
    return 0;
}
