#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
    vector<int> p;
    DSU(int n): p(n) { iota(p.begin(), p.end(), 0); }
    int find(int x) {
        return p[x] == x ? x : (p[x] = find(p[x]));
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        p[b] = a;
        return true;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> P(N);
    int maxP = 0;
    for(int i = 0; i < N; i++){
        cin >> P[i];
        maxP = max(maxP, P[i]);
    }

    // If values can be large, N must be small by problem's guarantees.
    // Use naive Kruskal in that case.
    if (maxP > 1000000) {
        struct Edge { int u, v, w; };
        vector<Edge> E;
        E.reserve((ll)N * (N - 1) / 2);
        for(int i = 0; i < N; i++){
            for(int j = i+1; j < N; j++){
                int a = P[i], b = P[j];
                // weight = max(a,b) % min(a,b)
                if (a < b) swap(a, b);
                int w = a % b;
                E.push_back({i, j, w});
            }
        }
        sort(E.begin(), E.end(),
             [](auto &A, auto &B){ return A.w < B.w; });
        DSU dsu(N);
        ll ans = 0;
        int used = 0;
        for(auto &e : E){
            if (dsu.unite(e.u, e.v)){
                ans += e.w;
                if (++used == N-1) break;
            }
        }
        cout << ans << "\n";
        return 0;
    }

    // Otherwise, maxP <= 1e6, possibly N large.
    // Build "alive" flags for distinct values.
    vector<char> alive(maxP+1, 0);
    for(int x : P) alive[x] = 1;

    // Count distinct values (each group of duplicates has zero-cost ties).
    int comps = 0;
    for(int v = 0; v <= maxP; v++){
        if (alive[v]) comps++;
    }
    if (comps <= 1){
        cout << 0 << "\n";
        return 0;
    }

    // Precompute nextAlive[v] = smallest w >= v with alive[w]==1 (or maxP+1)
    vector<int> nextAlive(maxP+2, maxP+1);
    for(int v = maxP; v >= 0; v--){
        nextAlive[v] = alive[v] ? v : nextAlive[v+1];
    }

    DSU dsu(maxP+1);
    ll answer = 0;

    // For each value i that exists, scan the residue-segments
    // [0..i-1], [i..2i-1], [2i..3i-1], ...
    // In each segment we link i to the first alive x in that segment
    // with weight = max(i,x) % min(i,x).
    for(int i = 1; i <= maxP && comps > 1; i++){
        if (!alive[i]) continue;
        ll j = 0;
        while(j <= maxP){
            int x = nextAlive[j];
            if (x > maxP) break;
            if (x < j + i){
                if (x != i) {
                    int u = dsu.find(i);
                    int v = dsu.find(x);
                    if (u != v){
                        dsu.unite(u, v);
                        answer += (i > x ? i % x : x % i);
                        if (--comps == 1) break;
                    }
                }
            }
            // jump to the start of the next segment
            ll k = (x < i ? 1LL : (x / i) + 1LL);
            j = k * i;
        }
    }

    cout << answer << "\n";
    return 0;
}
