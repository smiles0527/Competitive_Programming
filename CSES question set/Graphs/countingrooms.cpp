#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair

const int INF = 1e9;
const int MOD = 1e9+7;

int n, m;
vector<string> grid;

int prevstep[1000][1000];
char A[1000][1000];
bool vis[1000][1000];

//UDRL
int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, 1, -1};
string stepdir = "UDRL";

void dfs(int r, int c){
	vis[r][c] = true;
	for(int k = 0; k < 4; k++){
		int nr = r + dr[k];
		int nc = c + dc[k];

		if(nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
		if(vis[nr][nc]) continue;
		if(grid[nr][nc] == '#') continue;

		dfs(nr, nc);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m;
	grid.resize(n);
	for(int i = 0; i < n; i++) cin >> grid[i];

	int rooms = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(grid[i][j] == '.' && !vis[i][j]){
				dfs(i, j);
				rooms++;
			}
		}
	}
	cout << rooms <<'\n';

	
}
