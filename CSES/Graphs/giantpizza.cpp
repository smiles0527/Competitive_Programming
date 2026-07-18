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
bool vis[200005];
int comp[200005];
vector<int> order_;
int lit(int x, int val){ return 2*x + (val ? 0 : 1); }   // val=1 true node, 0 false node
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	int V = 2*(m+1);
	adj.assign(V, {}); radj.assign(V, {});
	auto add = [&](int u, int v){ adj[u].pb(v); radj[v].pb(u); };
	for(int i = 0; i < n; i++){
		char c1, c2; int a, b;
		cin >> c1 >> a >> c2 >> b;
		int la = lit(a, c1=='+'), lb = lit(b, c2=='+');  // the literals that satisfy
		add(la^1, lb);                                    // !la -> lb
		add(lb^1, la);                                    // !lb -> la
	}
	for(int st = 0; st < V; st++){
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
	for(int i = 1; i <= m; i++)
		if(comp[2*i] == comp[2*i+1]){ cout << "IMPOSSIBLE\n"; return 0; }
	string res(m, '-');
	for(int i = 1; i <= m; i++)
		res[i-1] = (comp[2*i] > comp[2*i+1]) ? '+' : '-';   // true node topologically later
	cout << res << '\n';
	return 0;
}