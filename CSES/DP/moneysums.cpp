#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    int sum = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    vector<bool> dp(sum + 1);
    dp[0] = true;

    int cur = 0;

    for (int x : a) {
        for (int s = cur + x; s >= x; s--) {
            if (dp[s - x]) dp[s] = true;
        }
        cur += x;
    }

    vector<int> ans;
    for (int s = 1; s <= sum; s++) {
        if (dp[s]) ans.push_back(s);
    }

    cout << ans.size() << '\n';

    for (int i = 0; i < (int)ans.size(); i++) {
        if (i) cout << ' ';
        cout << ans[i];
    }

    cout << '\n';
}
