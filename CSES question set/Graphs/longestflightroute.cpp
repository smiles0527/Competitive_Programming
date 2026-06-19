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
vector<vector<int>> adj;
int indeg[100005];
int dp[100005], nxt[100005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	adj.resize(n+1);
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		adj[a].pb(b);
		indeg[b]++;
	}
	queue<int> q;
	for(int i = 1; i <= n; i++)
		if(indeg[i] == 0) q.push(i);
	vector<int> order;
	while(!q.empty()){
		int v = q.front(); q.pop();
		order.pb(v);
		for(int to : adj[v])
			if(--indeg[to] == 0) q.push(to);
	}
	for(int i = 1; i <= n; i++){ dp[i] = INT_MIN; nxt[i] = -1; }
	dp[n] = 1;
	for(int i = (int)order.size()-1; i >= 0; i--){   // reverse topo
		int v = order[i];
		for(int to : adj[v]){
			if(dp[to] != INT_MIN && dp[to] + 1 > dp[v]){
				dp[v] = dp[to] + 1;
				nxt[v] = to;
			}
		}
	}
	if(dp[1] < 0){ cout << "IMPOSSIBLE\n"; return 0; }
	cout << dp[1] << '\n';
	vector<int> path;
	for(int v = 1; v != -1; v = nxt[v]) path.pb(v);
	for(int i = 0; i < (int)path.size(); i++)
		cout << path[i] << (i+1 == (int)path.size() ? '\n' : ' ');
	return 0;
}