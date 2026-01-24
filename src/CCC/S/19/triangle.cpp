#include <bits/stdc++.h>
using namespace std;

static inline size_t tri_idx(int i, int j) { return (size_t)i * (i - 1) / 2 + (j - 1); }
static inline size_t tri_cnt(int rows) { return (size_t)rows * (rows + 1) / 2; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    if (!(cin >> N >> K)) return 0;

    vector<int> cur(tri_cnt(N));
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= i; ++j)
            cin >> cur[tri_idx(i, j)];

    vector<int> sizes;
    {
        vector<int> seq;
        int t = K;
        seq.push_back(t);
        while (t > 2) { t = (2 * t + 2) / 3; seq.push_back(t); }
        seq.push_back(2);
        seq.push_back(1);
        sort(seq.begin(), seq.end());
        seq.erase(unique(seq.begin(), seq.end()), seq.end());
        for (int x : seq) if (x <= K) sizes.push_back(x);
        if (sizes.empty() || sizes.front() != 1) sizes.insert(sizes.begin(), 1);
    }

    int prev_sz = 1;
    for (int s : sizes) {
        if (s <= 1) { prev_sz = s; continue; }
        int d = s - prev_sz;
        int rows = N - s + 1;
        vector<int> nxt(tri_cnt(rows));
        for (int i = 1; i <= rows; ++i)
            for (int j = 1; j <= i; ++j) {
                int a = cur[tri_idx(i, j)];
                int b = cur[tri_idx(i + d, j)];
                int c = cur[tri_idx(i + d, j + d)];
                nxt[tri_idx(i, j)] = max(a, max(b, c));
            }
        cur.swap(nxt);
        prev_sz = s;
    }

    long long ans = 0;
    int rows = N - K + 1;
    for (int i = 1; i <= rows; ++i)
        for (int j = 1; j <= i; ++j)
            ans += cur[tri_idx(i, j)];

    cout << ans << '\n';
    return 0;
}
