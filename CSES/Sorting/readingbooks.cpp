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
	ll S = 0, M = 0;
	for(int i = 0; i < n; i++){
		ll t; cin >> t;
		S += t;
		M = max(M, t);
	}
	cout << max(S, 2*M) << '\n';
	return 0;
}