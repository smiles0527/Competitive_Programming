#include <bits/stdc++.h>
using namespace std;

const long long INF = 4000000000000000000LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<int> A(N + 1);
    vector<char> seen(N + 1, 0);
    int K = 0;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        if (!seen[A[i]]) {
            seen[A[i]] = 1;
            K++;
        }
    }

    int M = 3 * N;
    vector<int> B(M + 1);
    for (int i = 1; i <= M; i++) B[i] = A[(i - 1) % N + 1];

    vector<int> R(M + 2, M + 1);
    vector<int> L(M + 2, -1);

    {
        vector<int> cnt(N + 1, 0);
        int d = 0, r = 0;
        for (int l = 1; l <= 2 * N; l++) {
            while (r < M && d < K) {
                r++;
                int x = B[r];
                if (cnt[x]++ == 0) d++;
            }
            if (d == K) R[l] = r;
            int x = B[l];
            if (--cnt[x] == 0) d--;
        }
    }

    {
        vector<int> cnt(N + 1, 0);
        int d = 0, l = 1;
        for (int r = 1; r <= 3 * N; r++) {
            int x = B[r];
            if (cnt[x]++ == 0) d++;
            while (l <= r && d == K) {
                int y = B[l];
                if (cnt[y] > 1) {
                    cnt[y]--;
                    l++;
                } else {
                    break;
                }
            }
            if (d == K) L[r] = l;
        }
    }

    using P = pair<long long, int>;
    priority_queue<P, vector<P>, greater<P>> h1, h2;
    vector<long long> best(2 * N + 2, INF);

    for (int t = 1; t <= 2 * N; t++) {
        int rr = R[t];
        if (rr <= M) {
            h1.push({(long long)rr - 2LL * t, rr});
            h2.push({2LL * rr - (long long)t, rr});
        }

        while (!h1.empty() && h1.top().second < t) h1.pop();
        while (!h2.empty() && h2.top().second < t) h2.pop();

        if (!h1.empty()) best[t] = min(best[t], (long long)t + h1.top().first);
        if (!h2.empty()) best[t] = min(best[t], -(long long)t + h2.top().first);
        
        if (L[t] != -1) best[t] = min(best[t], (long long)t - L[t]);
    }

    for (int j = 1; j <= N; j++) {
        if (j > 1) cout << ' ';
        cout << min(best[j], best[j + N]);
    }
    cout << "\n";

    return 0;
}
