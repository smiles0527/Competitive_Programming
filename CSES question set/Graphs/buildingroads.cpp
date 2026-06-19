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
bool vis[100005];
vector<int> rep;

void dfs(int v){
	vis[v] = true;
	for(int to : adj[v]){
		if(!vis[to]){
			dfs(to);
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
		
	cin >> n >> m;
	adj.resize(n+1);
	for(int i = 0; i < m; i++){
		int a, b; 
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	for(int i = 1; i <= n; i++){
		if(!vis[i]){
			rep.push_back(i);
			dfs(i);
		}
	}
	cout << rep.size() - 1 << '\n';

	for(int i = 1; i < (int)rep.size(); i++){
		cout << rep[i-1] << ' ' << rep[i] << '\n';
	}
	return 0;
}
