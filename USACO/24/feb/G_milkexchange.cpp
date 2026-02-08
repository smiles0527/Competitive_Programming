#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    if (!(cin >> N)) return 0;
    vector<long long> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];
    int M = 3 * N;
    vector<long long> b(M);
    for (int i = 0; i < M; i++) b[i] = a[i % N];

    vector<int> P(M), R(M);
    {
        vector<int> st;
        for (int i = 0; i < M; i++) {
            while (!st.empty() && b[st.back()] >= b[i]) st.pop_back();
            P[i] = st.empty() ? -1 : st.back();
            st.push_back(i);
        }
    }
    {
        vector<int> st;
        for (int i = M - 1; i >= 0; i--) {
            while (!st.empty() && b[st.back()] > b[i]) st.pop_back();
            R[i] = st.empty() ? M : st.back();
            st.push_back(i);
        }
    }

    vector<long long> addK(N + 3, 0), addB(N + 3, 0);
    auto add_range = [&](int l, int r, long long p, long long q, long long w) {
        if (l > r) return;
        if (r<1 || l>N) return;
        l = max(l, 1); r = min(r, N);
        p *= w; q *= w;
        addK[l] += p; addK[r + 1] -= p;
        addB[l] += q; addB[r + 1] -= q;
        };

    for (int i = N; i <= 3 * N - 2; i++) {
        int L0 = i - P[i];
        int R0 = R[i] - i;
        int D = max(1, i - 2 * N + 2);
        int A = min(L0, i - N + 1);
        if (A <= 0 || A < D) continue;
        int t = D + R0 - 1;
        int U = A + R0 - 1;

        add_range(D, min(A, t), 1, 1 - D, b[i]);
        if (A >= t) add_range(t + 1, A, 0, R0, b[i]);
        else        add_range(A + 1, t, 0, A - D + 1, b[i]);
        add_range(max(A, t) + 1, U, -1, A + R0, b[i]);
    }

    vector<long long> ans(N + 2, 0);
    long long k = 0, c = 0;
    for (int L = 1; L <= N; L++) {
        k += addK[L];
        c += addB[L];
        ans[L] = k * L + c;
    }

    for (int t = 1; t <= N; t++) {
        int L = t + 1; if (L > N) L = N;
        cout << ans[L] << "\n";
    }
    return 0;
}
