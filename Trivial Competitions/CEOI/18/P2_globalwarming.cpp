#include <bits/stdc++.h>
using namespace std;

static long long a[200005];
static int L[200005];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n;
	long long x;
	cin >> n >> x;
	for (int i = 0; i < n; i++) cin >> a[i];

	vector<long long> dp(n, (long long)4e18);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int p = lower_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
		dp[p] = a[i];
		L[i] = p + 1;
		if (L[i] > ans) ans = L[i];
	}

	dp.assign(n, (long long)4e18);
	for (int i = n - 1; i >= 0; i--) {
		int p = lower_bound(dp.begin(), dp.end(), -a[i] + x) - dp.begin();
		ans = max(ans, L[i] + p);
		int q = lower_bound(dp.begin(), dp.end(), -a[i]) - dp.begin();
		dp[q] = -a[i];
	}

	cout << ans << '\n';
}
