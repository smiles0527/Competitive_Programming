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

    cin >> n;
    int V = 2 * n + 2;
    int S = 0, T = 2 * n + 1;
    hd.assign(V, -1);

    vector<vector<int>> eid(n + 1, vector<int>(n + 1));   // eid[i][j] = forward edge id i->task j
    for (int i = 1; i <= n; i++) ae(S, i, 1, 0);
    for (int j = 1; j <= n; j++) ae(n + j, T, 1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            ll c; cin >> c;
            eid[i][j] = ed.size();              // forward edge stored at this id
            ae(i, n + j, 1, c);
        }

    k = n;
    ll cost = 0; int flow = 0;
    vi dist(V), inq(V), pe(V);

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

    string out = to_string(cost) + "\n";
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (ed[eid[i][j]].cap == 0) {        // saturated forward edge = assignment
                out += to_string(i); out += ' '; out += to_string(j); out += '\n';
                break;
            }
    cout << out;
}