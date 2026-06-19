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
vector<string> grid;
int md[1000][1000], pd[1000][1000];
char par[1000][1000];
//DURL
int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, 1, -1};
string stepdir = "DURL";
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	grid.resize(n);
	ii A{-1, -1};
	queue<ii> q;
	for(int i = 0; i < n; i++){
		cin >> grid[i];
		for(int j = 0; j < m; j++){
			md[i][j] = pd[i][j] = INT_MAX;
			if(grid[i][j] == 'A') A = {i, j};
			if(grid[i][j] == 'M'){ md[i][j] = 0; q.push({i, j}); }
		}
	}
	while(!q.empty()){
		ii c = q.front(); q.pop();
		for(int k = 0; k < 4; k++){
			int nr = c.f + dr[k], nc = c.s + dc[k];
			if(nr<0||nr>=n||nc<0||nc>=m||grid[nr][nc]=='#'||md[nr][nc]!=INT_MAX) continue;
			md[nr][nc] = md[c.f][c.s] + 1;
			q.push({nr, nc});
		}
	}
	q.push(A); pd[A.f][A.s] = 0;
	ii g{-1, -1};
	if(md[A.f][A.s] > 0) while(!q.empty()){
		ii c = q.front(); q.pop();
		if(!c.f || c.f==n-1 || !c.s || c.s==m-1){ g = c; break; }
		for(int k = 0; k < 4; k++){
			int nr = c.f + dr[k], nc = c.s + dc[k];
			if(nr<0||nr>=n||nc<0||nc>=m||grid[nr][nc]=='#'||pd[nr][nc]!=INT_MAX) continue;
			if(pd[c.f][c.s]+1 >= md[nr][nc]) continue;
			pd[nr][nc] = pd[c.f][c.s] + 1;
			par[nr][nc] = stepdir[k];
			q.push({nr, nc});
		}
	}
	if(g.f == -1){ cout << "NO\n"; return 0; }
	string path;
	int r = g.f, c = g.s;
	while(r!=A.f || c!=A.s){
		char ch = par[r][c]; path.pb(ch);
		if(ch=='D') r--; else if(ch=='U') r++; else if(ch=='R') c--; else c++;
	}
	reverse(path.begin(), path.end());
	cout << "YES\n" << path.size() << '\n' << path << '\n';
	return 0;
}