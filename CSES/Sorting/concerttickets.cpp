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
int n, m;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	multiset<int> s;
	for(int i = 0, h; i < n; i++){ cin >> h; s.insert(h); }
	while(m--){
		int t; cin >> t;
		auto it = s.upper_bound(t);              // first price > t
		if(it == s.begin()){ cout << -1 << '\n'; continue; }
		--it;                                    // greatest price <= t
		cout << *it << '\n';
		s.erase(it);
	}
	return 0;
}