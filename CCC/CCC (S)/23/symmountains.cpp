#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int N; 
	if (!(cin >> N)) return 0;

	vector<long long> h(N);
	for (int i = 0; i < N; i++) cin >> h[i];
	vector<long long> best(N + 1, LLONG_MAX);
	best[1] = 0;
	for (int c = 0; c < N; c++) {
		long long s = 0;
		for (int k = 1; c - k >= 0 && c + k < N; k++) {
			s += llabs(h[c - k] - h[c + k]);
			int L = 2 * k + 1;
			if (s < best[L]) best[L] = s;
		}
	}
	for (int i = 0; i + 1 < N; i++) {
		long long s = llabs(h[i] - h[i + 1]);
		if (s < best[2]) best[2] = s;
		for (int k = 1; i - k >= 0 && i + 1 + k < N; k++) {
			s += llabs(h[i - k] - h[i + 1 + k]);
			int L = 2 * k + 2;
			if (s < best[L]) best[L] = s;
		}
	}
	for (int L = 1; L <= N; L++) {
		cout << best[L] << (L == N ? '\n' : ' ');
	}
}