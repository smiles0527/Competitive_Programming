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
struct E { int a, b; ll w; };
vector<E> edges;
ll dist[2505];
int par[2505];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for(int i = 0; i < m; i++){
		int a, b; ll w;
		cin >> a >> b >> w;
		edges.pb({a, b, w});
	}
	for(int i = 1; i <= n; i++){ dist[i] = 0; par[i] = -1; }
	int x = -1;
	for(int it = 0; it < n; it++){
		x = -1;
		for(E &e : edges){
			if(dist[e.a] + e.w < dist[e.b]){
				dist[e.b] = dist[e.a] + e.w;
				par[e.b] = e.a;
				x = e.b;
			}
		}
	}
	if(x == -1){ cout << "NO\n"; return 0; }
	for(int i = 0; i < n; i++) x = par[x];      // step into the cycle
	vector<int> cyc;
	for(int v = x; ; v = par[v]){
		cyc.pb(v);
		if(v == x && cyc.size() > 1) break;
	}
	reverse(cyc.begin(), cyc.end());
	cout << "YES\n";
	for(int i = 0; i < (int)cyc.size(); i++)
		cout << cyc[i] << (i+1 == (int)cyc.size() ? '\n' : ' ');
	return 0;
}