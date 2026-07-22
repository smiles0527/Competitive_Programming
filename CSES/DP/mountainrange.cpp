#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> h(n), l(n, -1), r(n, -1), st;
    vector<pair<int, int>> p(n);

    for (int i = 0; i < n; i++) {
        cin >> h[i];
        p[i] = {h[i], i};
    }

    for (int i = 0; i < n; i++) {
        while (!st.empty() && h[st.back()] <= h[i]) st.pop_back();
        if (!st.empty()) l[i] = st.back();
        st.push_back(i);
    }

    st.clear();

    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && h[st.back()] <= h[i]) st.pop_back();
        if (!st.empty()) r[i] = st.back();
        st.push_back(i);
    }

    sort(p.rbegin(), p.rend());

    vector<int> dp(n, 1);
    int ans = 1;

    for (int k = 0; k < n; k++) {
        int i = p[k].second;

        if (l[i] != -1) dp[i] = max(dp[i], dp[l[i]] + 1);
        if (r[i] != -1) dp[i] = max(dp[i], dp[r[i]] + 1);

        ans = max(ans, dp[i]);
    }

    cout << ans << '\n';
}
