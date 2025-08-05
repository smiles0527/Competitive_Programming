#include <bits/stdc++.h>
using namespace std;

static int freq[20000005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    if (!(cin >> N)) return 0;
    vector<long long> pref(N + 1);
    for (int i = 1; i <= N; ++i) {
        int x; cin >> x;
        pref[i] = pref[i - 1] + x;
    }

    const int MAXA = 100;
    const int OFFSET = MAXA * N;
    long long ans = 0;
    vector<int> used; used.reserve(N + 1);

    for (int D = 1; D <= MAXA; ++D) {
        used.clear();
        for (int i = 0; i <= N; ++i) {
            int idx = int(pref[i] - 1LL * D * i + OFFSET);
            ans += freq[idx];
            if (!freq[idx]) used.push_back(idx);
            ++freq[idx];
        }
        for (int idx : used) freq[idx] = 0;
    }

    cout << ans << '\n';
    return 0;
}
