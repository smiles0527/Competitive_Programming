#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<pair<int, int>> st; st.reserve(n);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        while (!st.empty() && st.back().first >= x) st.pop_back();
        if (i > 1) cout << ' ';
        cout << (st.empty() ? 0 : st.back().second);
        st.push_back({x, i});
    }
    cout << '\n';
}
