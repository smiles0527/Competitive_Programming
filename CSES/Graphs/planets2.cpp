#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int LOG = 18;
int n, q;
int t[200005];
int up[18][200005];
int col[200005], cyc[200005], pos_[200005], dep[200005], ent[200005];
bool onc[200005];
int clen[200005];
vector<vector<int>> rev;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    rev.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        dep[i] = -1;
    }
    for (int i = 1; i <= n; i++) rev[t[i]].push_back(i);

    int cc = 0;
    for (int i = 1; i <= n; i++) {
        if (col[i]) continue;
        int v = i;
        while (col[v] == 0) {
            col[v] = 1;
            v = t[v];
        }
        if (col[v] == 1) { // new cycle starting at v
            int c = v, p = 0, len = 0;
            do {
                onc[c] = true;
                cyc[c] = cc;
                pos_[c] = p++;
                dep[c] = 0;
                ent[c] = c;
                c = t[c];
                len++;
            } while (c != v);
            clen[cc++] = len;
        }
        v = i;
        while (col[v] == 1) {
            col[v] = 2;
            v = t[v];
        }
    }

    queue<int> bq;
    for (int i = 1; i <= n; i++)
        if (onc[i]) bq.push(i);
    while (!bq.empty()) { // reverse BFS over tails
        int y = bq.front();
        bq.pop();
        for (int x : rev[y]) {
            if (onc[x] || dep[x] != -1) continue;
            dep[x] = dep[y] + 1;
            cyc[x] = cyc[y];
            ent[x] = onc[y] ? y : ent[y];
            bq.push(x);
        }
    }

    for (int i = 1; i <= n; i++) up[0][i] = t[i];
    for (int j = 1; j < LOG; j++)
        for (int i = 1; i <= n; i++) up[j][i] = up[j - 1][up[j - 1][i]];

    while (q--) {
        int a, b;
        cin >> a >> b;
        ll res;
        if (onc[b]) {
            if (cyc[a] != cyc[b]) {
                cout << -1 << '\n';
                continue;
            }
            int e = ent[a], L = clen[cyc[b]];
            int arc = ((pos_[b] - pos_[e]) % L + L) % L;
            res = (ll)dep[a] + arc;
        } else {
            int d = dep[a] - dep[b];
            if (d < 0) {
                cout << -1 << '\n';
                continue;
            }
            int v = a;
            for (int j = 0; j < LOG; j++)
                if (d >> j & 1) v = up[j][v];
            if (v != b) {
                cout << -1 << '\n';
                continue;
            }
            res = d;
        }
        cout << res << '\n';
    }
}
