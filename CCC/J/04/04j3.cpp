#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

	int n, m; cin >> n >> m;
	vector<string> a(n); for(auto &x : a) cin >> x;
	vector<string> b(m); for(auto &x : b) cin >> x;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cout << a[i] << " as " << b[j];
		}
	}
	return 0;
}
