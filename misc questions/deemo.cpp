#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct VecHash {
    size_t operator()(vector<int> const& v) const noexcept {
        unsigned long long h = 1469598103934665603ULL;
        for (int x : v) {
            h ^= (unsigned long long)(x + 0x9e3779b97f4a7c15ULL);
            h *= 1099511628211ULL;
        }
        return (size_t)h;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> cnt(k+1, 0);
    unordered_map<vector<int>, long long, VecHash> freq;
    freq.reserve(n*2 + 10);
    vector<int> zeroKey(k-1, 0);
    freq[zeroKey] = 1;
    for (int i = 0; i < n; ++i) {
        int val = a[i];
        if (1 <= val && val <= k) cnt[val]++;
        vector<int> key;
        key.reserve(k-1);
        for (int j = 2; j <= k; ++j) key.push_back(cnt[j] - cnt[1]);
        freq[key]++;
    }
    long long ans = 0;
    for (auto &p : freq) {
        long long f = p.second;
        ans += f * (f - 1) / 2;
    }
    cout << ans << '\n';
    return 0;
}
