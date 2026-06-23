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
int par[100005], sz[100005];
struct E { ll a, b, c; };
vector<E> edges;
int find(int x){ while(par[x] != x) x = par[x] = par[par[x]]; return x; }
bool uni(int a, int b){
	a = find(a); b = find(b);
	if(a == b) return false;
	if(sz[a] < sz[b]) swap(a, b);
	par[b] = a; sz[a] += sz[b];
	return true;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for(int i = 0; i < m; i++){
		ll a, b, c;
		cin >> a >> b >> c;
		edges.pb({a, b, c});
	}
	sort(edges.begin(), edges.end(), [](const E &x, const E &y){ return x.c < y.c; });
	for(int i = 1; i <= n; i++){ par[i] = i; sz[i] = 1; }
	ll cost = 0;
	int used = 0;
	for(E &e : edges){
		if(uni(e.a, e.b)){ cost += e.c; used++; }
	}
	if(used < n-1) cout << "IMPOSSIBLE\n";
	else cout << cost << '\n';
	return 0;
}