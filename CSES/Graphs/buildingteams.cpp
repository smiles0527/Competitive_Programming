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
	vector<int> col(n+1, 0);
	queue<int> q;

	for(int i = 1; i <= n; i++){
		if(col[i] != 0) continue;
		col[i] = 1;
		q.push(i);
		while(!q.empty()){
			int v = q.front();
			q.pop();
			for(int to : adj[v]){
				if(col[to] == 0){
					col[to] = 3 - col[v];
					q.push(to);
				} else if (col[to] == col[v]){
					cout << "IMPOSSIBLE\n";
					return 0;
				}
			}
		}
	}
	for(int i = 1; i <= n; i++){
		cout << col[i] << (i == n ? '\n' : ' ');
	}
	return 0;
}