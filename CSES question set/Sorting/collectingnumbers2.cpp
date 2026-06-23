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
int arr[200005], pos[200005];
int breaks = 0;
bool isbreak(int v){                              // contributes if pos[v+1] < pos[v]
	if(v < 1 || v+1 > n) return false;
	return pos[v+1] < pos[v];
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		cin >> arr[i];
		pos[arr[i]] = i;
	}
	for(int v = 1; v < n; v++) if(isbreak(v)) breaks++;
	while(m--){
		int a, b;
		cin >> a >> b;
		int u = arr[a], w = arr[b];
		// affected adjacency indices: {u-1,u,w-1,w}, dedup
		set<int> aff = {u-1, u, w-1, w};
		for(int v : aff) if(isbreak(v)) breaks--;   // remove old contributions
		swap(arr[a], arr[b]);
		pos[u] = b; pos[w] = a;
		for(int v : aff) if(isbreak(v)) breaks++;   // add new contributions
		cout << (breaks + 1) << '\n';
	}
	return 0;
}