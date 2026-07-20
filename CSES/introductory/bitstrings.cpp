#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	ll n; cin >> n;
	ll ans = 1;
 
	for(int i=0;i<n;i++){
		ans *= 2;
		ans %= MOD;
	}
 
	cout << ans << '\n';
	return 0;
}
