#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N, C;
    if (!(cin >> N >> C)) return 0;
    vector<long long> P(N);
    for (long long i = 0; i < N; ++i) cin >> P[i];
    sort(P.begin(), P.end());
    
    long long L = (C % 2 == 0) ? (C/2 - 1) : (C/2);
    vector<long long> B(2*N);
    for (long long i = 0; i < N; ++i) {
        B[i] = P[i];
        B[i+N] = P[i] + C;
    }
    long long bad = 0;
    long long j = 0;
    for (long long i = 0; i < N; ++i) {
        if (j < i) j = i;
        while (j + 1 < i + N && B[j + 1] - B[i] <= L) ++j;
        long long k = j - i;
        bad += k * (k - 1) / 2;
    }
    
    if (C % 2 == 0) {
        long long half = C / 2;
        vector<long long> uniq, cnt;
        for (long long i = 0; i < N; ) {
            long long v = P[i], c = 0;
            while (i < N && P[i] == v) { ++c; ++i; }
            uniq.push_back(v);
            cnt.push_back(c);
        }
        vector<long long> prefVals = uniq;
        for (size_t idx = 0; idx < uniq.size(); ++idx) {
            long long x = uniq[idx];
            if (x >= half) continue;
            long long y = x + half;
            auto it = lower_bound(uniq.begin(), uniq.end(), y);
            if (it == uniq.end() || *it != y) continue;
            long long idy = it - uniq.begin();
            long long a = cnt[idx], b = cnt[idy];
            if (a && b) {
                bad += a * b * (N - a - b);
                bad += (a * (a - 1) / 2) * b;
                bad += (b * (b - 1) / 2) * a;
            }
        }
    }
    
    long long total = N * (N - 1) * (N - 2) / 6;
    cout << (total - bad) << "\n";
    return 0;
}
