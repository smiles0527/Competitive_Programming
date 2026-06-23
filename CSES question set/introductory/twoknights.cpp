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
	
	ll n; cin >> n;
	for(ll i=1;i<=n;i++){
		ll total = i*i*(i*i-1)/2;
		ll attack = 4*(i-1)*(i-2);
		cout << total - attack << '\n';
	}
 
	return 0;
}