#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int MOD = 1e9+7;
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