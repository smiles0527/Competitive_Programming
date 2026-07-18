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
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	ll n; cin >> n;
	
	vector<vector<int>> dist(n, vector<int>(n, -1));
	queue<pair<int, int>> q;
 
	dist[0][0] = 0;
	q.push({0, 0});
 
	int dr[8] = {2, 2, -2, -2, 1, 1, -1, -1};
	int dc[8] = {1, -1, 1, -1, 2, -2, 2, -2};
 
	while(!q.empty()){
		auto [r, c] = q.front();
		q.pop();
		for(int i = 0; i < 8; i++){
			int nr = r + dr[i], nc = c + dc[i];
			if(0 <= nr && nr < n && 0 <= nc && nc < n && dist[nr][nc] == -1){
				dist[nr][nc] = dist[r][c]+1;
				q.push({nr, nc});
			}
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
		cout << dist[i][j] << (j + 1 == n ? '\n' : ' ');
		}
	}
	return 0;
}