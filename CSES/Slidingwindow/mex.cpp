#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> q(k), cnt(k + 1);
    set<int> s;
    for (int i = 0; i <= k; i++) s.insert(i);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if (i >= k) {
            int y = q[i % k];
            if (y <= k && --cnt[y] == 0) s.insert(y);
        }

        q[i % k] = x;
        if (x <= k && cnt[x]++ == 0) s.erase(x);

        if (i >= k - 1) {
            if (i >= k) cout << ' ';
            cout << *s.begin();
        }
    }

    cout << '\n';
}
