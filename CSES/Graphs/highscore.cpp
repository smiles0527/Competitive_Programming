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
int n, m;
struct E { int a, b; ll w; };
vector<E> edges;
ll dist[2505];
bool inf[2505];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for(int i = 0; i < m; i++){
		int a, b; ll w;
		cin >> a >> b >> w;
		edges.pb({a, b, -w});          // negate -> shortest path
	}
	for(int i = 1; i <= n; i++) dist[i] = INF;
	dist[1] = 0;
	for(int it = 0; it < n-1; it++)
		for(E &e : edges)
			if(dist[e.a] != INF && dist[e.a] + e.w < dist[e.b])
				dist[e.b] = dist[e.a] + e.w;
	for(int it = 0; it < n; it++)        // propagate -inf marks
		for(E &e : edges)
			if(dist[e.a] != INF && (dist[e.a] + e.w < dist[e.b] || inf[e.a])){
				dist[e.b] = dist[e.a] + e.w;
				inf[e.b] = true;
			}
	if(inf[n]) cout << -1 << '\n';
	else cout << -dist[n] << '\n';
	return 0;
}