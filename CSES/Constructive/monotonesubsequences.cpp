#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, k;
        cin >> n >> k;

        if (n > k * k) {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        for (int l = 1; l <= n; l += k) {
            int r = min(n, l + k - 1);
            for (int x = r; x >= l; --x) cout << x << ' ';
        }
        cout << '\n';
    }
}