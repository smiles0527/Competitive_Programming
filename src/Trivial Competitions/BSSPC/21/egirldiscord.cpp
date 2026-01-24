#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    if(!(cin >> N >> K)) return 0;
    vector<long long> minpref(K, (long long)4e18);
    long long ans = 0, pref = 0;
    minpref[0] = 0;
    for (int i = 1; i <= N; ++i) {
        long long x; cin >> x;
        pref += x;
        int r = i % K;
        if (minpref[r] < (long long)4e18) ans = max(ans, pref - minpref[r]);
        minpref[r] = min(minpref[r], pref);
    }
    cout << ans << '\n';
    return 0;
}
