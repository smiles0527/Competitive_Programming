#include "towns.h"
#include <bits/stdc++.h>
using namespace std;

static int d[105][105];

static int D(int i, int j) {
    if (i == j) return 0;
    int a = min(i, j), b = max(i, j);
    int &r = d[a][b];
    if (r == -1) r = getDistance(i, j);
    return r;
}

static bool chk(int n, int p, int dm, int du[], int dv[]) {
    int h = n / 2, l = 0, r = 0;
    vector<int> m;

    for (int i = 0; i < n; i++) {
        int a = (du[i] + dm - dv[i]) >> 1;
        if (a < p) l++;
        else if (a > p) r++;
        else m.push_back(i);
    }

    if (l > h || r > h) return false;
    if (m.empty()) return true;

    auto same = [&](int x, int y) {
        return du[x] + du[y] - D(x, y) > (p << 1);
    };

    int cand = -1, cnt = 0;
    for (int x : m) {
        if (!cnt) cand = x, cnt = 1;
        else if (same(cand, x)) cnt++;
        else cnt--;
    }

    if (cand == -1) return true;

    int sz = 0;
    for (int x : m) if (same(cand, x)) sz++;
    return sz <= h;
}

int hubDistance(int N, int sub) {
    memset(d, -1, sizeof(d));

    int d0[105], du[105], dv[105];
    int u = 0, v = 0;

    d0[0] = 0;
    for (int i = 1; i < N; i++) {
        d0[i] = D(0, i);
        if (d0[i] > d0[u]) u = i;
    }

    du[u] = 0;
    v = u;
    for (int i = 0; i < N; i++) {
        if (i == u) continue;
        du[i] = D(u, i);
        if (du[i] > du[v]) v = i;
    }

    int dm = du[v];

    dv[v] = 0;
    for (int i = 0; i < N; i++) {
        if (i == v) continue;
        dv[i] = D(v, i);
    }

    vector<int> pos;
    for (int i = 0; i < N; i++) {
        if (i == u || i == v) continue;
        int a = (du[i] + dm - dv[i]) >> 1;
        if (0 < a && a < dm) pos.push_back(a);
    }

    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());

    int R = 1e9;
    vector<int> cand;
    for (int p : pos) {
        int cur = max(p, dm - p);
        if (cur < R) R = cur, cand = {p};
        else if (cur == R) cand.push_back(p);
    }

    if (sub <= 2) return R;

    for (int p : cand) if (chk(N, p, dm, du, dv)) return R;
    return -R;
}