#include <bits/stdc++.h>
using namespace std;
#define ll long long
using i128 = __int128_t;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll a, b, k, t; 
	cin >> a >> b >> k >> t;

	ll d = llabs(b-a);
	ll q = d/k, m1 = LLONG_MAX, m2 = LLONG_MAX;

	for(ll x = max(0LL, q-2); x<=q+2 ;x++ ){
		ll c = x + llabs(d-x*k);
		if(c < m1) m2 = m1, m1=c;
		else if (c > m1 && c < m2) m2 = c;
	}


	//min 1 2
	if(t==1) cout << m1 << '\n';
	else cout << min(m2, m1 +2) << '\n';
}