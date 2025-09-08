#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)4e18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    vector<int> breed(N+1);
    for(int i = 1; i <= N; ++i) cin >> breed[i];

    vector<string> S(K+1);
    for(int i = 1; i <= K; ++i){
        cin >> S[i];
        S[i] = ' ' + S[i];
    }

    vector<vector<int>> pos(K+1);
    pos.reserve(K+1);
    for(int i = 1; i <= N; ++i)
        pos[breed[i]].push_back(i);

    vector<ll> dist(N+1, INF);
    dist[1] = 0;
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    pq.emplace(0, 1);

    while(!pq.empty()){
        auto [d, u] = pq.top(); pq.pop();
        if(d != dist[u]) continue;
        if(u == N) break;
        int pb = breed[u];
        for(int tb = 1; tb <= K; ++tb){
            if(S[pb][tb] != '1') continue;
            auto &vlist = pos[tb];
            int sz = (int)vlist.size();
            if(sz == 0) continue;
            int idx = int(lower_bound(vlist.begin(), vlist.end(), u) - vlist.begin());
            if(idx < sz && vlist[idx] == u){
                if(idx > 0){
                    int v = vlist[idx-1];
                    ll nd = d + ll(u - v);
                    if(nd < dist[v]){
                        dist[v] = nd;
                        pq.emplace(nd, v);
                    }
                }
                if(idx+1 < sz){
                    int v = vlist[idx+1];
                    ll nd = d + ll(v - u);
                    if(nd < dist[v]){
                        dist[v] = nd;
                        pq.emplace(nd, v);
                    }
                }
            } else {
                if(idx > 0){
                    int v = vlist[idx-1];
                    ll nd = d + ll(u - v);
                    if(nd < dist[v]){
                        dist[v] = nd;
                        pq.emplace(nd, v);
                    }
                }
                if(idx < sz){
                    int v = vlist[idx];
                    ll nd = d + ll(v - u);
                    if(nd < dist[v]){
                        dist[v] = nd;
                        pq.emplace(nd, v);
                    }
                }
            }
            {
                int v = vlist[0];
                ll nd = d + abs(u - v);
                if(nd < dist[v]){
                    dist[v] = nd;
                    pq.emplace(nd, v);
                }
            }
            {
                int v = vlist.back();
                ll nd = d + abs(u - v);
                if(nd < dist[v]){
                    dist[v] = nd;
                    pq.emplace(nd, v);
                }
            }
        }
    }

    cout << (dist[N] < INF ? dist[N] : -1) << "\n";
    return 0;
}