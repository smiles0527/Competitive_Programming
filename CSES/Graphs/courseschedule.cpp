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
	if((int)order.size() < n){ cout << "IMPOSSIBLE\n"; return 0; }
	for(int i = 0; i < n; i++)
		cout << order[i] << (i+1 == n ? '\n' : ' ');
	return 0;
}