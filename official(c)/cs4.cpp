#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
struct Tunnel {
    int a, b;
    ll c;
};
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;
    vector<Tunnel> tunnels(M);
    vector<vector<ll>> roomLevels(N+1);
    for (int i = 0; i < M; i++){
        int a, b; ll c;
        cin >> a >> b >> c;
        tunnels[i] = {a, b, c};
        roomLevels[a].push_back(c);
        roomLevels[b].push_back(c);
    }
    roomLevels[1].push_back(0);
    vector<vector<pair<ll,int>>> mapping(N+1);
    int totalNodes = 0;
    for (int i = 1; i <= N; i++){
        sort(roomLevels[i].begin(), roomLevels[i].end());
        roomLevels[i].erase(unique(roomLevels[i].begin(), roomLevels[i].end()), roomLevels[i].end());
        mapping[i].resize(roomLevels[i].size());
        for (int j = 0; j < (int)roomLevels[i].size(); j++){
            mapping[i][j] = {roomLevels[i][j], totalNodes++};
        }
    }
    vector<vector<pair<int,ll>>> graph(totalNodes);
    for (int i = 1; i <= N; i++){
        for (int j = 0; j + 1 < (int)mapping[i].size(); j++){
            int u = mapping[i][j].second, v = mapping[i][j+1].second;
            ll cost = mapping[i][j+1].first - mapping[i][j].first;
            graph[u].push_back({v, cost});
            graph[v].push_back({u, cost});
        }
    }
    for (auto &t : tunnels){
        int a = t.a, b = t.b;
        ll c = t.c;
        int u = -1, v = -1;
        {
            auto &vec = mapping[a];
            int lo = 0, hi = vec.size()-1;
            while(lo <= hi){
                int mid = (lo+hi)/2;
                if(vec[mid].first == c){ u = vec[mid].second; break; }
                else if(vec[mid].first < c) lo = mid+1;
                else hi = mid-1;
            }
        }
        {
            auto &vec = mapping[b];
            int lo = 0, hi = vec.size()-1;
            while(lo <= hi){
                int mid = (lo+hi)/2;
                if(vec[mid].first == c){ v = vec[mid].second; break; }
                else if(vec[mid].first < c) lo = mid+1;
                else hi = mid-1;
            }
        }
        if(u != -1 && v != -1){
            graph[u].push_back({v,0});
            graph[v].push_back({u,0});
        }
    }
    int start = -1;
    for(auto &p : mapping[1]){
        if(p.first == 0){ start = p.second; break; }
    }
    vector<ll> dist(totalNodes, LLONG_MAX);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    dist[start] = 0;
    pq.push({0, start});
    while(!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();
        if(d != dist[u]) continue;
        for(auto &edge : graph[u]){
            int v = edge.first;
            ll w = edge.second;
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    ll ans = LLONG_MAX;
    for(auto &p : mapping[N]){
        ans = min(ans, dist[p.second]);
    }
    cout << ans;
    return 0;
}
