#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p;
    vector<int> term;
    DSU(int n): p(n + 1, -1), term(n + 1, 0) {}
    int rep(int x) { return p[x] < 0 ? x : p[x] = rep(p[x]); }
    int sz(int x) { return -p[rep(x)]; }
    void make_cycle(int x) { term[rep(x)] = 0; }
    void join_to(int x, int y) {
        int rx = rep(x), ry = rep(y);
        if (rx == ry) {
            term[rx] = 0;
            return;
        }
        int newTerm = term[ry];
        if (p[rx] > p[ry]) swap(rx, ry);
        p[rx] += p[ry];
        p[ry] = rx;
        term[rx] = newTerm;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> to0(N + 1);
    for (int i = 1; i <= N; i++) cin >> to0[i];

    int Q;
    cin >> Q;

    vector<int> type(Q), x(Q);
    vector<int> will_del(N + 1, 0);
    for (int i = 0; i < Q; i++) {
        cin >> type[i] >> x[i];
        if (type[i] == 2) will_del[x[i]] = 1;
    }

    vector<int> to = to0;
    for (int i = 1; i <= N; i++) if (will_del[i]) to[i] = 0;

    DSU uf(N);

    for (int i = 1; i <= N; i++) {
        if (to[i] != 0) uf.join_to(i, to[i]);
    }

    for (int i = 1; i <= N; i++) {
        if (to[i] == 0) {
            int r = uf.rep(i);
            if (uf.term[r] == 0) uf.term[r] = i;
        }
    }

    vector<string> out;
    out.reserve(Q);

    for (int i = Q - 1; i >= 0; i--) {
        if (type[i] == 1) {
            int r = uf.rep(x[i]);
            int t = uf.term[r];
            if (t == 0) out.push_back("CIKLUS");
            else out.push_back(to_string(t));
        } else {
            int v = x[i];
            int u = to0[v];
            to[v] = u;
            uf.join_to(v, u);
        }
    }

    for (int i = (int)out.size() - 1; i >= 0; i--) {
        cout << out[i] << "\n";
    }

    return 0;
}
