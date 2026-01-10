#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> good(n + 1, 1);
    vector<int> pts;
    pts.reserve(n);

    vector<int> dp(n + 1, 0);
    dp[0] = 1;

    long long sum[2] = {1, 0};

    int lp = 0;
    int recR = 0;

    for (int i = 1; i <= n; i++) {
        good[i] = 1;

        if (i - 1 >= 1 && s[i - 2] == 'B') pts.push_back(i - 1);

        vector<int> npts;
        npts.reserve(pts.size());
        for (int p : pts) {
            int q = p - 1;
            if (q >= 0) {
                if (good[q]) {
                    good[q] = 0;
                    if (q >= lp) {
                        sum[q & 1] -= dp[q];
                        sum[q & 1] %= MOD;
                        if (sum[q & 1] < 0) sum[q & 1] += MOD;
                    }
                }
                npts.push_back(q);
            }
        }
        pts.swap(npts);

        if (s[i - 1] == 'R') recR = i;

        int bound = 2 * recR - i - 1;
        if (bound < 0) bound = 0;

        while (lp < bound) {
            if (good[lp]) {
                sum[lp & 1] -= dp[lp];
                sum[lp & 1] %= MOD;
                if (sum[lp & 1] < 0) sum[lp & 1] += MOD;
            }
            lp++;
        }
        while (lp > bound) {
            lp--;
            if (good[lp]) {
                sum[lp & 1] += dp[lp];
                sum[lp & 1] %= MOD;
            }
        }

        long long notPaint = (s[i - 1] == 'X') ? dp[i - 1] : 0LL;
        long long val = notPaint + sum[i & 1];
        val %= MOD;
        dp[i] = (int)val;

        sum[i & 1] += dp[i];
        sum[i & 1] %= MOD;
    }

    cout << dp[n] << "\n";
    return 0;
}