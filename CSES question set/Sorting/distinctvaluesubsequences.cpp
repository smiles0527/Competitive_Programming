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
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	unordered_map<int,int> cnt;
	cnt.reserve(2*n);
	for(int i = 0, x; i < n; i++){ cin >> x; cnt[x]++; }
	ll prod = 1;
	for(auto &e : cnt) prod = prod * ((e.s + 1) % MOD) % MOD;
	ll ans = (prod - 1 + MOD) % MOD;
	cout << ans << '\n';
	return 0;
}