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
int x, n;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> x >> n;
	vector<int> p(n);
	for(auto &v : p) cin >> v;

	set<int> pts;
	pts.insert(0); pts.insert(x);
	for(int v : p) pts.insert(v);

	multiset<int> gaps;
	{
		int prev = -1;
		for(int v : pts){
			if(prev != -1) gaps.insert(v - prev);
			prev = v;
		}
	}

	vector<int> ans(n);
	for(int i = n - 1; i >= 0; i--){
		ans[i] = *gaps.rbegin();                  // max gap with first i+1 lights present
		int v = p[i];
		auto it = pts.find(v);
		auto nx = next(it), pv = prev(it);
		int R = *nx, L = *pv;
		gaps.erase(gaps.find(R - v));             // remove the two adjacent gaps
		gaps.erase(gaps.find(v - L));
		gaps.insert(R - L);                       // merge
		pts.erase(it);
	}
	for(int i = 0; i < n; i++) cout << ans[i] << (i+1 == n ? '\n' : ' ');
	return 0;
}