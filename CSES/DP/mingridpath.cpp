#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> g(n);
    for (int i = 0; i < n; i++) cin >> g[i];

    string ans(1, g[0][0]);
    vector<int> cur(1, 0), nxt, seen(n, -1);

    for (int d = 0; d < 2 * n - 2; d++) {
        char best = 'Z';

        for (int i : cur) {
            int j = d - i;
            if (i + 1 < n) best = min(best, g[i + 1][j]);
            if (j + 1 < n) best = min(best, g[i][j + 1]);
        }

        ans += best;
        nxt.clear();

        for (int i : cur) {
            int j = d - i;

            if (i + 1 < n && g[i + 1][j] == best && seen[i + 1] != d) {
                seen[i + 1] = d;
                nxt.push_back(i + 1);
            }

            if (j + 1 < n && g[i][j + 1] == best && seen[i] != d) {
                seen[i] = d;
                nxt.push_back(i);
            }
        }

        cur.swap(nxt);
    }

    cout << ans << '\n';
}
