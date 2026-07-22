#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;

    unordered_map<int, int> last;
    last.reserve(2 * n);
    last.max_load_factor(0.7);

    int l = 0, ans = 0;

    for (int r = 0; r < n; r++) {
        int x; cin >> x;

        auto it = last.find(x);
        if (it != last.end()) l = max(l, it->second + 1);

        last[x] = r;
        ans = max(ans, r - l + 1);
    }

    cout << ans << '\n';
}
