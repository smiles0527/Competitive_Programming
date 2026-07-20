#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int R, T, K;
    cin >> R >> T >> K;
    vector<int> mem(K);
    for (auto &x : mem) cin >> x;

    vector<vector<int>> fb(R);
    long long M = 0;
    for (int f = 0; f < R; f++){
        int c; cin >> c;
        fb[f].resize(c);
        for (auto &x : fb[f]) cin >> x;
        M += c;
    }

    vector<vector<int>> inc(T + 1);              // faces incident to each town
    struct Ed{ int lo, hi, f; };
    vector<Ed> es; es.reserve(M);
    for (int f = 0; f < R; f++){
        int c = fb[f].size();
        for (int i = 0; i < c; i++){
            int u = fb[f][i];
            inc[u].push_back(f);
            int v = fb[f][(i + 1 == c) ? 0 : i + 1];
            es.push_back({min(u, v), max(u, v), f});
        }
    }
    fb.clear(); fb.shrink_to_fit();

    sort(es.begin(), es.end(), [](const Ed&a, const Ed&b){
        return a.lo != b.lo ? a.lo < b.lo : a.hi < b.hi;
    });

    // vector<vector<int>> g(R);                 // dual graph -> CSR below (cache/TLE)
    // for (size_t i = 0; i < es.size(); ){
    //     size_t j = i;
    //     while (j < es.size() && es[j].lo == es[i].lo && es[j].hi == es[i].hi) j++;
    //     for (size_t a = i; a < j; a++)
    //         for (size_t b = a + 1; b < j; b++)
    //             if (es[a].f != es[b].f){
    //                 g[es[a].f].push_back(es[b].f);
    //                 g[es[b].f].push_back(es[a].f);
    //             }
    //     i = j;
    // }

    vector<int> ea, eb;                          // paired half-edges -> dual edges
    for (size_t i = 0; i < es.size(); ){
        size_t j = i;
        while (j < es.size() && es[j].lo == es[i].lo && es[j].hi == es[i].hi) j++;
        for (size_t a = i; a < j; a++)
            for (size_t b = a + 1; b < j; b++)
                if (es[a].f != es[b].f){ ea.push_back(es[a].f); eb.push_back(es[b].f); }  // skip bridge self-loops
        i = j;
    }
    es.clear(); es.shrink_to_fit();

    vector<int> deg(R + 1, 0);
    for (size_t e = 0; e < ea.size(); e++){ deg[ea[e]]++; deg[eb[e]]++; }
    vector<int> off(R + 1, 0);
    for (int f = 0; f < R; f++) off[f + 1] = off[f] + deg[f];
    vector<int> adj(off[R]);
    vector<int> cur(off.begin(), off.end());
    for (size_t e = 0; e < ea.size(); e++){
        adj[cur[ea[e]]++] = eb[e];
        adj[cur[eb[e]]++] = ea[e];
    }
    ea.clear(); ea.shrink_to_fit(); eb.clear(); eb.shrink_to_fit();

    vector<long long> tot(R, 0);
    // vector<int> dist(R), q; q.reserve(R);     // old: O(R) fill per round (TLE)
    vector<int> dist(R, 0), stamp(R, -1), q(R);
    for (int rnd = 0; rnd < K; rnd++){
        int m = mem[rnd], qt = 0;
        // fill(dist.begin(), dist.end(), -1);    // avoided via stamp
        for (int f : inc[m]) if (stamp[f] != rnd){ stamp[f] = rnd; dist[f] = 0; q[qt++] = f; }
        for (int h = 0; h < qt; h++){
            int u = q[h];
            for (int p = off[u]; p < off[u + 1]; p++){
                int w = adj[p];
                if (stamp[w] != rnd){ stamp[w] = rnd; dist[w] = dist[u] + 1; q[qt++] = w; }
            }
        }
        for (int i = 0; i < qt; i++){ int f = q[i]; tot[f] += dist[f]; }   // dual connected => qt == R
    }

    long long best = LLONG_MAX; int bf = 0;
    for (int f = 0; f < R; f++) if (tot[f] < best){ best = tot[f]; bf = f; }
    cout << best << "\n" << bf + 1 << "\n";
    return 0;
}