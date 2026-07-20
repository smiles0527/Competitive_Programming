#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n; cin >> n;
	vector<ll> a(n);
	ll sum = 0;
	for(auto &x : a) cin >> x, sum += x;
	
	ll best = (ll)4e18;
	for(int i = 0; i < (1 << n); i++){
		ll x = 0;
		for(int j = 0; j < n; j++) if( i & (1 << j)) x += a[j];
		best = min(best, llabs(sum - 2 * x));
	}
 
	cout << best << '\n';
	return 0;
}
