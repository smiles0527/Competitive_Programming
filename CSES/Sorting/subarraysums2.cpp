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
ll x;
struct H {
	size_t operator()(ll k) const {
		k += 0x9e3779b97f4a7c15ULL;
		k = (k ^ (k >> 30)) * 0xbf58476d1ce4e5b9ULL;
		k = (k ^ (k >> 27)) * 0x94d049bb133111ebULL;
		return k ^ (k >> 31);
	}
};
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> x;
	unordered_map<ll,ll,H> cnt;
	cnt.reserve(2*n);
	cnt[0] = 1;                                  // empty prefix
	ll pre = 0, ans = 0;
	for(int i = 0; i < n; i++){
		ll v; cin >> v;
		pre += v;
		auto it = cnt.find(pre - x);
		if(it != cnt.end()) ans += it->s;        // earlier prefixes giving sum x
		cnt[pre]++;
	}
	cout << ans << '\n';
	return 0;
}