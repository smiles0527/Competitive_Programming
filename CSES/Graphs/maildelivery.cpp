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
vector<vector<ii>> adj;        // {neighbor, edge id}
vector<bool> used;
int it_[100005];
int deg[100005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	adj.resize(n+1);
	used.assign(m, false);
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		adj[a].pb({b, i});
		adj[b].pb({a, i});
		deg[a]++; deg[b]++;
	}
	for(int i = 1; i <= n; i++)
		if(deg[i] & 1){ cout << "IMPOSSIBLE\n"; return 0; }

	vector<int> circuit;
	vector<int> stk; stk.pb(1);
	while(!stk.empty()){
		int v = stk.back();
		while(it_[v] < (int)adj[v].size() && used[adj[v][it_[v]].s]) it_[v]++;
		if(it_[v] == (int)adj[v].size()){
			circuit.pb(v);
			stk.pop_back();
		} else {
			ii e = adj[v][it_[v]++];
			if(used[e.s]) continue;
			used[e.s] = true;
			stk.pb(e.f);
		}
	}
	if((int)circuit.size() != m + 1){ cout << "IMPOSSIBLE\n"; return 0; }  // disconnected
	reverse(circuit.begin(), circuit.end());
	for(int i = 0; i < (int)circuit.size(); i++)
		cout << circuit[i] << (i+1 == (int)circuit.size() ? '\n' : ' ');
	return 0;
}