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
int n, mm, k, S, T, V;
struct Edge { int to; ll cap; };
vector<Edge> es;
vector<int> g[1005];
int level_[1005], it_[1005];
void add(int a, int b, ll c){
	g[a].pb(es.size()); es.pb({b, c});
	g[b].pb(es.size()); es.pb({a, 0});
}
bool bfs(){
	for(int i = 0; i < V; i++) level_[i] = -1;
	queue<int> q; q.push(S); level_[S] = 0;
	while(!q.empty()){
		int v = q.front(); q.pop();
		for(int id : g[v])
			if(es[id].cap > 0 && level_[es[id].to] < 0){
				level_[es[id].to] = level_[v] + 1;
				q.push(es[id].to);
			}
	}
	return level_[T] >= 0;
}
ll dfs(int v, ll pushed){
	if(v == T) return pushed;
	for(int &i = it_[v]; i < (int)g[v].size(); i++){
		int id = g[v][i], to = es[id].to;
		if(es[id].cap > 0 && level_[to] == level_[v] + 1){
			ll d = dfs(to, min(pushed, es[id].cap));
			if(d > 0){ es[id].cap -= d; es[id^1].cap += d; return d; }
		}
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> mm >> k;
	S = 0; T = n + mm + 1; V = n + mm + 2;
	for(int i = 1; i <= n; i++) add(S, i, 1);          // source -> boys
	for(int j = 1; j <= mm; j++) add(n + j, T, 1);     // girls -> sink
	vector<int> firstEdge;                              // id of boy->girl arcs
	for(int i = 0; i < k; i++){
		int a, b;
		cin >> a >> b;
		firstEdge.pb(es.size());
		add(a, n + b, 1);                               // boy -> girl
	}
	int flow = 0;
	while(bfs()){
		for(int i = 0; i < V; i++) it_[i] = 0;
		while(dfs(S, INF) > 0) flow++;
	}
	cout << flow << '\n';
	for(int id : firstEdge){
		if(es[id].cap == 0){                            // saturated -> matched
			int boy = es[id^1].to;                      // reverse arc points back to boy
			int girl = es[id].to - n;
			cout << boy << ' ' << girl << '\n';
		}
	}
	return 0;
}