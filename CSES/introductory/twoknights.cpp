#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	ll n; cin >> n;
	for(ll i=1;i<=n;i++){
		ll total = i*i*(i*i-1)/2;
		ll attack = 4*(i-1)*(i-2);
		cout << total - attack << '\n';
	}
 
	return 0;
}
