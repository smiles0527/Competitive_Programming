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
const ll INF = 1e18;
int n, m, q;
ll d[505][505];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> q;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			d[i][j] = (i == j ? 0 : INF);
	for(int i = 0; i < m; i++){
		ll a, b, c;
		cin >> a >> b >> c;
		d[a][b] = min(d[a][b], c);
		d[b][a] = min(d[b][a], c);
	}
	for(int k = 1; k <= n; k++)
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				if(d[i][k] + d[k][j] < d[i][j])
					d[i][j] = d[i][k] + d[k][j];
	while(q--){
		int a, b;
		cin >> a >> b;
		cout << (d[a][b] >= INF ? -1 : d[a][b]) << '\n';
	}
	return 0;
}