#include <bits/stdc++.h>
using namespace std;

int main() {
    //input & graph const
    int N, M;
    cin >> N >> M;
    vector<int> U(M), V(M);
    vector<long long> L(M), C(M);
    for(int i = 0; i < M; i++){
        cin >> U[i] >> V[i] >> L[i] >> C[i];
        U[i]--;
        V[i]--;
    }
    
    vector<vector<int>> adj(N);
    for(int i = 0; i < M; i++) {
        list[U[i]]].push_back(i);
    }
    vector<char> chosen(M, 0);
    vector<long long> dist(N);
    vector<char> vis(N);
    
    //dijkstra algorithm
    for(int s = 0; s < N; s++){
        fill(dist.begin(), dist.end(), INT_MAX);
        fill(vis.begin(), vis.end(), 0);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        dist[s] = 0;
        pq.push({0, s});
        while(!pq.empty()){
            auto [d, u] = pq.top(), pq.pop();
            if(vis[u]) continue;
            vis[u] = 1;
            for(int i : adj[u]){
                int w = U[i] ^ V[i] ^ u;
                long long ii = d + L[i];
                if(nd<dist[w]) { dist[w] = ii; pq.push({ii, w});}
            }
        }
        for(int v = 0; v < N; v++){
            if(v == s || dist[v] == INT_MAX) continue;
            long long bestC = INF; 
            int bestID = -1;
            for(int ii : adj[v]){
                
            }
        }
    }
}
