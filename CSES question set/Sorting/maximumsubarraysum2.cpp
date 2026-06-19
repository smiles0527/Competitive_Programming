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
int n, a, b;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> a >> b;
	vector<ll> pre(n+1, 0);
	for(int i = 1; i <= n; i++){
		ll v; cin >> v;
		pre[i] = pre[i-1] + v;
	}
	deque<int> dq;                               // indices, increasing pre
	ll best = LLONG_MIN;
	for(int r = a; r <= n; r++){
		int add = r - a;                         // newly eligible left index
		while(!dq.empty() && pre[dq.back()] >= pre[add]) dq.pop_back();
		dq.pb(add);
		int lo = r - b;                          // expire indices < lo
		while(!dq.empty() && dq.front() < lo) dq.pop_front();
		best = max(best, pre[r] - pre[dq.front()]);
	}
	cout << best << '\n';
	return 0;
}