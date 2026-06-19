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
	vector<ll> cntRes(n, 0);
	cntRes[0] = 1;                               // empty prefix, residue 0
	ll pre = 0, ans = 0;
	for(int i = 0; i < n; i++){
		ll v; cin >> v;
		pre += v;
		int r = (int)(((pre % n) + n) % n);      // normalized residue
		ans += cntRes[r];                        // pairs with same residue seen before
		cntRes[r]++;
	}
	cout << ans << '\n';
	return 0;
}