#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int n;
vector<vector<int>> trans;

void gen(int row, int mask, int next) {
    if (row == n) {
        trans[mask].push_back(next);
        return;
    }

    if (mask & (1 << row)) {
        gen(row + 1, mask, next);
        return;
    }

    gen(row + 1, mask, next | (1 << row));

    if (row + 1 < n && !(mask & (1 << (row + 1)))) {
        gen(row + 2, mask, next);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m; cin >> n >> m;

    int states = 1 << n;
    trans.resize(states);

    for (int mask = 0; mask < states; mask++) gen(0, mask, 0);

    vector<int> dp(states), ndp(states);
    dp[0] = 1;

    for (int col = 0; col < m; col++) {
        fill(ndp.begin(), ndp.end(), 0);

        for (int mask = 0; mask < states; mask++) {
            for (int next : trans[mask]) {
                ndp[next] += dp[mask];
                if (ndp[next] >= MOD) ndp[next] -= MOD;
            }
        }

        dp.swap(ndp);
    }

    cout << dp[0] << '\n';
}
