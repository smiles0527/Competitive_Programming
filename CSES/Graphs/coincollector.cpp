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
vector<vector<int>> adj, radj;
bool vis[100005];
int comp[100005];
ll coin[100005];
vector<int> order_;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	adj.resize(n+1); radj.resize(n+1);
	for(int i = 1; i <= n; i++) cin >> coin[i];
	vector<ii> ed(m);
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		adj[a].pb(b);
		radj[b].pb(a);
		ed[i] = {a, b};
	}
	for(int st = 1; st <= n; st++){
		if(vis[st]) continue;
		vector<pair<int,int>> stk; stk.pb({st, 0});
		vis[st] = true;
		while(!stk.empty()){
			int v = stk.back().f;
			int &i = stk.back().s;
			if(i < (int)adj[v].size()){
				int to = adj[v][i++];
				if(!vis[to]){ vis[to] = true; stk.pb({to, 0}); }
			} else { order_.pb(v); stk.pop_back(); }
		}
	}
	int k = 0;
	for(int idx = (int)order_.size()-1; idx >= 0; idx--){
		int st = order_[idx];
		if(comp[st]) continue;
		k++;
		vector<int> stk; stk.pb(st); comp[st] = k;
		while(!stk.empty()){
			int v = stk.back(); stk.pop_back();
			for(int to : radj[v])
				if(!comp[to]){ comp[to] = k; stk.pb(to); }
		}
	}
	vector<ll> val(k+1, 0), dp(k+1, 0);
	for(int i = 1; i <= n; i++) val[comp[i]] += coin[i];
	vector<vector<int>> dag(k+1);
	for(auto &e : ed){
		int cu = comp[e.f], cv = comp[e.s];
		if(cu != cv) dag[cu].pb(cv);             // condensation edges
	}
	// comp labels are in topological order (label 1 = source); process descending = reverse topo
	for(int c = k; c >= 1; c--){
		ll best = 0;
		for(int d : dag[c]) best = max(best, dp[d]);
		dp[c] = val[c] + best;
	}
	ll ans = 0;
	for(int c = 1; c <= k; c++) ans = max(ans, dp[c]);
	cout << ans << '\n';
	return 0;
}