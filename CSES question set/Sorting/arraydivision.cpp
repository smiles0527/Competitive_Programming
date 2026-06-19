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
int n, k;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> k;
	vector<ll> x(n);
	ll lo = 0, hi = 0;
	for(auto &v : x){ cin >> v; lo = max(lo, v); hi += v; }

	auto need = [&](ll S)->int{                  // subarrays needed with cap S
		int cnt = 1;
		ll cur = 0;
		for(ll v : x){
			if(cur + v > S){ cnt++; cur = v; }
			else cur += v;
		}
		return cnt;
	};

	while(lo < hi){
		ll mid = lo + (hi - lo) / 2;
		if(need(mid) <= k) hi = mid;
		else lo = mid + 1;
	}
	cout << lo << '\n';
	return 0;
}