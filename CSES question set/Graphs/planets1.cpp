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
const int LOG = 30;
int n, q;
int up[30][200005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> q;
	for(int i = 1; i <= n; i++) cin >> up[0][i];
	for(int j = 1; j < LOG; j++)
		for(int i = 1; i <= n; i++)
			up[j][i] = up[j-1][up[j-1][i]];
	while(q--){
		int x, k;
		cin >> x >> k;
		for(int j = 0; j < LOG; j++)
			if(k >> j & 1) x = up[j][x];
		cout << x << '\n';
	}
	return 0;
}