#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 5;
const long long INF = 1000000000000LL;

long long dp[MAXN];
long long seg[6 * MAXN], lazy[6 * MAXN];
long long a[MAXN];
int st[MAXN];

void pushdown(int id) {
    if (!lazy[id]) return;
    lazy[id << 1] += lazy[id];
    lazy[id << 1 | 1] += lazy[id];
    seg[id << 1] += lazy[id];
    seg[id << 1 | 1] += lazy[id];
    lazy[id] = 0;
}

void pushup(int id) {
    seg[id] = max(seg[id << 1], seg[id << 1 | 1]);
}

void update(int id, int l, int r, int ql, int qr, long long v) {
    if (ql > qr) return;
    if (ql <= l && r <= qr) {
        lazy[id] += v;
        seg[id] += v;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(id);
    if (ql <= mid) update(id << 1, l, mid, ql, qr, v);
    if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, v);
    pushup(id);
}

long long query(int id, int l, int r, int ql, int qr) {
    if (ql > qr) return LLONG_MIN / 4;
    if (ql <= l && r <= qr) return seg[id];
    int mid = (l + r) >> 1;
    pushdown(id);
    long long res = LLONG_MIN / 4;
    if (ql <= mid) res = max(res, query(id << 1, l, mid, ql, qr));
    if (qr > mid) res = max(res, query(id << 1 | 1, mid + 1, r, ql, qr));
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) return 0;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    int top = 0;
    for (int i = 1; i <= n; ++i) {
        while (top && a[st[top]] <= a[i]) {
            int pos = st[top];
            int left = (top > 1 ? st[top - 1] : 0);
            update(1, 0, n, left, pos - 1, a[i] - a[pos]);
            --top;
        }
        st[++top] = i;
        update(1, 0, n, i - 1, i - 1, dp[i - 1] + a[i]);
        long long best = query(1, 0, n, max(0, i - k), i - 1);
        dp[i] = best - INF;
    }

    long long days = (n + k - 1) / k;
    long long ans = dp[n] + days * INF;
    cout << ans << '\n';

    return 0;
}
