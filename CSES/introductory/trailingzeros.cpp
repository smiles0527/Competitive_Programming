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
	ll ans = 0;
 
	for(ll i=5;i<=n;i*=5)
		ans += n/i;
 
	cout << ans << '\n';
	return 0;
}