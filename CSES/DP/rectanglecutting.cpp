#include <bits/stdc++.h>
using namespace std;

int dp[501][501];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;

    for (int h = 1; h <= a; h++) {
        for (int w = 1; w <= b; w++) {
            if (h == w) continue;

            dp[h][w] = 1e9;

            for (int k = 1; k < h; k++) {
                dp[h][w] = min(dp[h][w], dp[k][w] + dp[h - k][w] + 1);
            }

            for (int k = 1; k < w; k++) {
                dp[h][w] = min(dp[h][w], dp[h][k] + dp[h][w - k] + 1);
            }
        }
    }

    cout << dp[a][b] << '\n';
}
