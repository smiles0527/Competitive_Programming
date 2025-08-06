#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;
    int total = M * N;
    vector<vector<pair<int,int>>> inv(1000001);
    vector<vector<int>> A(M+1, vector<int>(N+1));
    for(int i = 1; i <= M; i++){
        for(int j = 1; j <= N; j++){
            cin >> A[i][j];
            inv[A[i][j]].emplace_back(i, j);
        }
    }

    vector<vector<bool>> vis(M+1, vector<bool>(N+1, false));
    queue<pair<int,int>> q;
    vis[M][N] = true;
    q.emplace(M, N);

    while(!q.empty()){
        auto [r, c] = q.front(); q.pop();
        int prod = r * c;
        if(prod <= 1000000){
            for(auto &p : inv[prod]){
                int i = p.first, j = p.second;
                if(!vis[i][j]){
                    vis[i][j] = true;
                    q.emplace(i, j);
                }
            }
            inv[prod].clear();
        }
    }

    cout << (vis[1][1] ? "yes\n" : "no\n");
    return 0;
}
