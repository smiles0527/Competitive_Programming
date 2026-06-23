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
int n;
ll t;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> t;
	vector<ll> k(n);
	ll mn = LLONG_MAX;
	for(auto &v : k){ cin >> v; mn = min(mn, v); }

	auto ok = [&](ll T)->bool{
		ll cnt = 0;
		for(ll v : k){
			cnt += T / v;
			if(cnt >= t) return true;            // early exit avoids overflow
		}
		return cnt >= t;
	};

	ll lo = 1, hi = mn * t;                       // fastest machine alone
	while(lo < hi){
		ll mid = lo + (hi - lo) / 2;
		if(ok(mid)) hi = mid;
		else lo = mid + 1;
	}
	cout << lo << '\n';
	return 0;
}