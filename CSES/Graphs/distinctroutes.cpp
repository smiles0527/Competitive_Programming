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
struct Edge { int to; ll cap; };
vector<Edge> es;
vector<int> g[505];
int level_[505], it_[505];
void add(int a, int b, ll c){
	g[a].pb(es.size()); es.pb({b, c});
	g[b].pb(es.size()); es.pb({a, 0});
}
bool bfs(int s, int t){
	for(int i = 1; i <= n; i++) level_[i] = -1;
	queue<int> q; q.push(s); level_[s] = 0;
	while(!q.empty()){
		int v = q.front(); q.pop();
		for(int id : g[v])
			if(es[id].cap > 0 && level_[es[id].to] < 0){
				level_[es[id].to] = level_[v] + 1;
				q.push(es[id].to);
			}
	}
	return level_[t] >= 0;
}
ll dfs(int v, int t, ll pushed){
	if(v == t) return pushed;
	for(int &i = it_[v]; i < (int)g[v].size(); i++){
		int id = g[v][i], to = es[id].to;
		if(es[id].cap > 0 && level_[to] == level_[v] + 1){
			ll d = dfs(to, t, min(pushed, es[id].cap));
			if(d > 0){ es[id].cap -= d; es[id^1].cap += d; return d; }
		}
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		add(a, b, 1);
	}
	int flow = 0;
	while(bfs(1, n)){
		for(int i = 1; i <= n; i++) it_[i] = 0;
		while(dfs(1, n, INF) > 0) flow++;
	}
	cout << flow << '\n';
	vector<vector<int>> paths;
	for(int p = 0; p < flow; p++){
		vector<int> route;
		int v = 1;
		route.pb(1);
		while(v != n){
			for(int id : g[v]){
				// forward arc that carried flow: original cap 1 now 0, and it's a forward (even id) arc
				if((id % 2 == 0) && es[id].cap == 0 && es[id^1].cap == 1){
					es[id].cap = 1;                 // consume: mark used by restoring? no—mark
					es[id^1].cap = 0;
					v = es[id].to;
					route.pb(v);
					break;
				}
			}
		}
		paths.pb(route);
	}
	for(auto &r : paths){
		cout << r.size() << '\n';
		for(int i = 0; i < (int)r.size(); i++)
			cout << r[i] << (i+1 == (int)r.size() ? '\n' : ' ');
	}
	return 0;
}