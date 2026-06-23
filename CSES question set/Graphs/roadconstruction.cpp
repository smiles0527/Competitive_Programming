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
int par[100005], sz[100005];
int find(int x){ while(par[x] != x) x = par[x] = par[par[x]]; return x; }
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for(int i = 1; i <= n; i++){ par[i] = i; sz[i] = 1; }
	int comp = n, mx = 1;
	while(m--){
		int a, b;
		cin >> a >> b;
		a = find(a); b = find(b);
		if(a != b){
			if(sz[a] < sz[b]) swap(a, b);
			par[b] = a; sz[a] += sz[b];
			comp--;
			mx = max(mx, sz[a]);
		}
		cout << comp << ' ' << mx << '\n';
	}
	return 0;
}