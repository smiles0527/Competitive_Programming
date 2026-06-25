#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;
const ll INF = 1e18;

int n, m, k;
struct Edge { int to, cap; ll cost; int nxt; };
vector<Edge> ed;
vi hd;

void ae(int u, int v, int cap, ll cost) {       // add edge + residual
    ed.pb({v, cap, cost, (int)hd[u]}); hd[u] = ed.size() - 1;
    ed.pb({u, 0, -cost, (int)hd[v]}); hd[v] = ed.size() - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    hd.assign(n + 1, -1);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        ae(a, b, 1, 1);                          // teleporter: cap 1, cost 1
    }

    int S = 1, T = n;
    ll cost = 0; int flow = 0;
    vi dist(n + 1), inq(n + 1), pe(n + 1);

    while (flow < k) {
        fill(dist.begin(), dist.end(), INF);
        fill(inq.begin(), inq.end(), 0);
        dist[S] = 0;
        deque<int> q; q.pb(S); inq[S] = 1;
        while (!q.empty()) {                     // SPFA: cheapest residual path
            int u = q.front(); q.pop_front(); inq[u] = 0;
            for (int e = hd[u]; e != -1; e = ed[e].nxt) {
                if (ed[e].cap > 0 && dist[u] + ed[e].cost < dist[ed[e].to]) {
                    dist[ed[e].to] = dist[u] + ed[e].cost;
                    pe[ed[e].to] = e;
                    if (!inq[ed[e].to]) { inq[ed[e].to] = 1; q.pb(ed[e].to); }
                }
            }
        }
        if (dist[T] == INF) break;

        int push = k - flow;
        for (int v = T; v != S; v = ed[pe[v] ^ 1].to) push = min(push, ed[pe[v]].cap);
        for (int v = T; v != S; v = ed[pe[v] ^ 1].to) {
            ed[pe[v]].cap -= push;
            ed[pe[v] ^ 1].cap += push;
        }
        flow += push;
        cost += (ll)push * dist[T];
    }

    if (flow < k) { cout << -1 << "\n"; return 0; }

    // decompose unit flow into k routes: follow saturated forward edges (cap now 0)
    string out = to_string(cost) + "\n";
    for (int r = 0; r < k; r++) {
        vector<int> path = {1};
        int u = 1;
        while (u != n) {
            for (int e = hd[u]; e != -1; e = ed[e].nxt) {
                if (!(e & 1) && ed[e].cap == 0) {     // even id = real forward edge, used
                    ed[e].cap = 1;                    // consume so next route won't reuse
                    u = ed[e].to;
                    path.pb(u);
                    break;
                }
            }
        }
        out += to_string(path.size()) + "\n";
        for (int i = 0; i < (int)path.size(); i++) {
            out += to_string(path[i]);
            out += (i + 1 < (int)path.size()) ? ' ' : '\n';
        }
    }
    cout << out;
}