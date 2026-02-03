#include <bits/stdc++.h>
using namespace std;

vector<int> rt;

struct DSU {
    vector<int> p;
    DSU(int n): p(n, -1) {}
    int rep(int x) { return p[x] < 0 ? x : p[x] = rep(p[x]); }
    int sz(int x) { return -p[rep(x)]; }
    bool join(int x, int y) {
        x = rep(x); y = rep(y);
        if (x == y) return false;
        int r = rt[y];
        if (p[x] > p[y]) swap(x, y);
        p[x] += p[y];
        p[y] = x;
        rt[x] = r;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    rt.assign(N + 1, 0);
    vector<int> nx(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> nx[i];
        rt[i] = i;
    }

    int M;
    cin >> M;

    vector<int> qs(M);
    vector<vector<int>> ts(N + 1);

    for (int i = 0; i < M; i++) {
        int idx;
        char c;
        cin >> idx >> c;
        qs[i] = idx;
        int t = (c == 'C' ? 0 : (c == 'O' ? 1 : 2));
        ts[idx].push_back(t);
    }

    reverse(qs.begin(), qs.end());

    DSU uf(N + 1);

    for (int i = 1; i <= N; i++) if (ts[i].empty()) uf.join(i, nx[i]);

    array<long long, 3> ans = {0, 0, 0};
    for (int i = 1; i <= N; i++) if (!ts[i].empty()) ans[ts[i].back()] += uf.sz(i);

    vector<array<long long, 3>> res;
    res.reserve(M + 1);
    res.push_back(ans);

    for (int i : qs) {
        ans[ts[i].back()] -= uf.sz(i);
        ts[i].pop_back();

        if (!ts[i].empty()) {
            ans[ts[i].back()] += uf.sz(i);
        } else {
            int s = uf.sz(i);
            uf.join(i, nx[i]);
            int r = rt[uf.rep(i)];
            if (!ts[r].empty()) ans[ts[r].back()] += s;
        }
        res.push_back(ans);
    }

    reverse(res.begin(), res.end());
    res.erase(res.begin());

    for (auto &v : res) {
        cout << v[0] << " " << v[1] << " " << v[2] << "\n";
    }
    return 0;
}
