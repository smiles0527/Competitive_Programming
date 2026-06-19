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
int dr[8] = {1, 1, -1, -1, 2, 2, -2, -2};
int dc[8] = {2, -2, 2, -2, 1, -1, 1, -1};
int board[8][8];
bool inb(int r, int c){ return r >= 0 && r < 8 && c >= 0 && c < 8; }
int deg(int r, int c){
	int d = 0;
	for(int k = 0; k < 8; k++){
		int nr = r + dr[k], nc = c + dc[k];
		if(inb(nr, nc) && board[nr][nc] == 0) d++;
	}
	return d;
}
bool solve(int r, int c, int step){
	board[r][c] = step;
	if(step == 64) return true;
	vector<pair<int,ii>> cand;
	for(int k = 0; k < 8; k++){
		int nr = r + dr[k], nc = c + dc[k];
		if(inb(nr, nc) && board[nr][nc] == 0)
			cand.pb({deg(nr, nc), {nr, nc}});
	}
	sort(cand.begin(), cand.end());
	for(auto &e : cand){
		int nr = e.s.f, nc = e.s.s;
		if(solve(nr, nc, step + 1)) return true;
	}
	board[r][c] = 0;
	return false;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int x, y;
	cin >> x >> y;
	int c = x - 1, r = y - 1;
	solve(r, c, 1);
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			cout << board[i][j] << (j == 7 ? '\n' : ' ');
	return 0;
}