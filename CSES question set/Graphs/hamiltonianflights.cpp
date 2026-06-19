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
int cnt[20][20];                  // cnt[v][u]: number of edges v->u
int dp[1<<20][20];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		cnt[a-1][b-1]++;
	}
	dp[1][0] = 1;                  // start at city 0 (=1), set {0}
	for(int S = 1; S < (1<<n); S++){
		if(!(S & 1)) continue;     // must contain start
		for(int v = 0; v < n; v++){
			if(!dp[S][v] || !(S >> v & 1)) continue;
			int cur = dp[S][v];
			for(int u = 0; u < n; u++){
				if((S >> u & 1) || !cnt[v][u]) continue;     // u visited or no edge
				int &t = dp[S | (1<<u)][u];
				t = (t + (ll)cur * cnt[v][u]) % MOD;          // multiply by edge multiplicity
			}
		}
	}
	cout << dp[(1<<n)-1][n-1] << '\n';
	return 0;
}