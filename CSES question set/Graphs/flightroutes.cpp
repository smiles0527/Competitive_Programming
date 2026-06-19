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
int n, m, k;
vector<vii> adj;
int cnt[100005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> k;
	adj.resize(n+1);
	for(int i = 0; i < m; i++){
		ll a, b, c;
		cin >> a >> b >> c;
		adj[a].pb({b, c});
	}
	priority_queue<ii, vii, greater<ii>> pq;
	pq.push({0, 1});
	vi ans;
	while(!pq.empty()){
		ii cur = pq.top(); pq.pop();
		ll d = cur.f, v = cur.s;
		if(cnt[v] >= k) continue;
		cnt[v]++;
		if(v == n) ans.pb(d);
		if(cnt[v] == k && v == n) break;       // collected all k for target
		for(ii e : adj[v]){
			ll to = e.f, w = e.s;
			if(cnt[to] < k) pq.push({d + w, to});
		}
	}
	for(int i = 0; i < k; i++) cout << ans[i] << (i+1 == k ? '\n' : ' ');
	return 0;
}