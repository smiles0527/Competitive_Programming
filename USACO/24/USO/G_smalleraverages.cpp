#include <bits/stdc++.h>
using namespace std;

const int MOD = 1'000'000'007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
        b[i] += b[i - 1];
    }

    vector<vector<int>> ro(n + 1), co(n + 1);

    for (int i = 1; i <= n; ++i) {
        ro[i].resize(i);
        co[i].resize(i);
        iota(ro[i].begin(), ro[i].end(), 0);
        iota(co[i].begin(), co[i].end(), 0);

        sort(ro[i].begin(), ro[i].end(), [&](int x, int y) {
            return (a[i] - a[x]) * (i - y)
                 < (a[i] - a[y]) * (i - x);
        });

        sort(co[i].begin(), co[i].end(), [&](int x, int y) {
            return (b[i] - b[x]) * (i - y)
                 < (b[i] - b[y]) * (i - x);
        });
    }

    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    dp[0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        const auto &rord = ro[i];
        vector<vector<int>> ps(i, vector<int>(n + 1));

        for (int r = 0; r < i; ++r) {
            int x = rord[r];
            for (int y = 0; y <= n; ++y) {
                ps[r][y] = dp[x][y];
                if (r) {
                    ps[r][y] += ps[r - 1][y];
                    if (ps[r][y] >= MOD) ps[r][y] -= MOD;
                }
            }
        }

        for (int j = 1; j <= n; ++j) {
            int r = 0;

            for (int y : co[j]) {
                while (r < i) {
                    int x = rord[r];

                    long long lhs = (a[i] - a[x]) * (j - y);
                    long long rhs = (b[j] - b[y]) * (i - x);

                    if (lhs > rhs) break;
                    ++r;
                }

                if (r) {
                    dp[i][j] += ps[r - 1][y];
                    if (dp[i][j] >= MOD) dp[i][j] -= MOD;
                }
            }
        }
    }

    cout << dp[n][n] << '\n';
    return 0;
}