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
	vector<ii> ev;
	ev.reserve(2*n);
	for(int i = 0; i < n; i++){
		int a, b;
		cin >> a >> b;
		ev.pb({a, 1});                           // arrival
		ev.pb({b, -1});                          // departure
	}
	sort(ev.begin(), ev.end());
	int cur = 0, best = 0;
	for(auto &e : ev){
		cur += e.s;
		best = max(best, cur);
	}
	cout << best << '\n';
	return 0;
}