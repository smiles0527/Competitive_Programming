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
vector<vii> adj;
ll dist[100005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	adj.resize(n+1);
	for(int i = 0; i < m; i++){
		ll a, b, c;
		cin >> a >> b >> c;
		adj[a].pb({b, c});
	}
	for(int i = 1; i <= n; i++) dist[i] = LLONG_MAX;
	dist[1] = 0;
	priority_queue<ii, vii, greater<ii>> pq;
	pq.push({0, 1});
	while(!pq.empty()){
		ii cur = pq.top(); pq.pop();
		ll d = cur.f, v = cur.s;
		if(d > dist[v]) continue;
		for(ii e : adj[v]){
			ll to = e.f, w = e.s;
			if(dist[v] + w < dist[to]){
				dist[to] = dist[v] + w;
				pq.push({dist[to], to});
			}
		}
	}
	for(int i = 1; i <= n; i++) cout << dist[i] << (i == n ? '\n' : ' ');
	return 0;
}