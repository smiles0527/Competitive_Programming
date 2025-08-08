#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)1e18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<vector<int>> d(N+1, vector<int>(N+1));
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cin >> d[i][j];
        }
    }

    int M;
    cin >> M;
    vector<bool> cookie(N+1, false);
    for(int i = 0; i < M; i++){
        int t;
        cin >> t;
        cookie[t] = true;
    }

    vector<vector<ll>> dist(2, vector<ll>(N+1, INF));
    vector<vector<int>> ways(2, vector<int>(N+1, 0));
    int init = cookie[1] ? 1 : 0;
    dist[init][1] = 0;
    ways[init][1] = 1;

    using T = tuple<ll,int,int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    pq.emplace(0, 1, init);

    while(!pq.empty()){
        auto [cd, u, h] = pq.top();
        pq.pop();
        if(cd > dist[h][u]) continue;
        for(int v = 1; v <= N; v++){
            if(v == u) continue;
            ll w = d[u][v];
            int nh = h | (cookie[v] ? 1 : 0);
            ll nd = cd + w;
            if(nd < dist[nh][v]){
                dist[nh][v] = nd;
                ways[nh][v] = ways[h][u];
                pq.emplace(nd, v, nh);
            }
            else if(nd == dist[nh][v]){
                ways[nh][v] = (ways[nh][v] + ways[h][u]) % 1000000;
            }
        }
    }

    cout << dist[1][N] << " " << ways[1][N] << "\n";
    return 0;
}
