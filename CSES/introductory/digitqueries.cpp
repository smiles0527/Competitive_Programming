#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	ll q; cin >> q;	
	while(q--){
		ll k; cin >> k;
 
		ll d = 1; ll s = 1;
		while(true){
			__int128 cnt = 9;
			for(int i = 1; i < d; i++) cnt *= 10;
			__int128 block = cnt * d;
			if((__int128)k > block){
				k -= (long long) block;
				d++;
				s *= 10;
			} else break;
		}
		ll idx = k-1;
		ll add = idx / d;
		ll pos = idx % d;
		ll x = s + add;
		
		string ss = to_string(x);
		cout << ss[(int)pos] << '\n';
	}
	return 0;
}
