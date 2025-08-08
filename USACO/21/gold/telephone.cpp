#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 4e18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    vector<int> breed(N+1);
    for(int i = 1; i <= N; ++i) 
        cin >> breed[i];

    vector<string> canSend(K+1);
    for(int i = 1; i <= K; ++i){
        cin >> canSend[i];
        canSend[i] = ' ' + canSend[i];  // 1-index
    }

    vector< set<int> > alive(K+1);
    for(int i = 1; i <= N; ++i)
        alive[breed[i]].insert(i);

    vector<ll> dist(N+1, INF);
    dist[1] = 0;
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    pq.emplace(0, 1);

    while(!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();
        if(d != dist[u]) continue;
        int pb = breed[u];

        for(int tb = 1; tb <= K; ++tb){
            if(canSend[pb][tb] != '1') continue;
            auto &st = alive[tb];

            // scan to the right of u
            auto it = st.lower_bound(u);
            while(it != st.end()){
                int v = *it;
                ll nd = d + ll(abs(u - v));
                if(nd < dist[v]){
                    dist[v] = nd;
                    pq.emplace(nd, v);
                    it = st.erase(it);
                } else break;
            }
            // scan to the left of u
            it = st.lower_bound(u);
            while(it != st.begin()){
                auto jt = prev(it);
                int v = *jt;
                ll nd = d + ll(abs(u - v));
                if(nd < dist[v]){
                    dist[v] = nd;
                    pq.emplace(nd, v);
                    st.erase(jt);
                } else break;
            }
            
        }
    }

    ll ans = dist[N] < INF ? dist[N] : -1;
    cout << ans << "\n";
    return 0;
}
