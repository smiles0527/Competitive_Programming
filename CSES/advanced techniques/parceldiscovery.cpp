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
vi hd;                                          // head_[u] -> first edge id (long for vi)

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
        int a, b, r; ll c;
        cin >> a >> b >> r >> c;
        ae(a, b, r, c);
    }

    int S = 1, T = n;
    ll cost = 0; int flow = 0;
    vi dist(n + 1), inq(n + 1), pe(n + 1);      // pe = parent edge id

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
        if (dist[T] == INF) break;               // no augmenting path

        int push = k - flow;                     // bottleneck clamped to remaining need
        for (int v = T; v != S; v = ed[pe[v] ^ 1].to) push = min(push, ed[pe[v]].cap);
        for (int v = T; v != S; v = ed[pe[v] ^ 1].to) {
            ed[pe[v]].cap -= push;
            ed[pe[v] ^ 1].cap += push;
        }
        flow += push;
        cost += (ll)push * dist[T];
    }

    cout << (flow == k ? cost : -1) << "\n";
}