#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> q(k);
    unordered_map<int, int> cnt;
    cnt.reserve(2 * k);
    cnt.max_load_factor(0.7);

    int cur = 0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if (i >= k) {
            int y = q[i % k];
            if (--cnt[y] == 0) {
                cnt.erase(y);
                cur--;
            }
        }

        q[i % k] = x;
        if (cnt[x]++ == 0) cur++;

        if (i >= k - 1) {
            if (i >= k) cout << ' ';
            cout << cur;
        }
    }

    cout << '\n';
}
