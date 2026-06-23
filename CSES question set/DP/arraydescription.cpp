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
	
	int n, m; cin >> n >> m;
	vector<int> x(n);
	for(auto &a : x) cin >> a;

	vi prev(m+2,0), cur(m+2,0);

	for(int v=1;v<=m;v++) if(x[0]==0 || x[0]==v) prev[v]=1;

	for(int i=1;i<n;i++){
		fill(cur.begin(),cur.end(),0);
		for(int v=1;v<=m;v++){
			if(x[i]!=0&&x[i]!=v)continue;
			cur[v]=(prev[v-1]+prev[v]+prev[v+1])%MOD;
		}
		swap(prev,cur);	
	}
	
	ll ans=0;
	for(int v=1;v<=m;v++) ans = (ans+prev[v])%MOD;
	cout << ans;

	return 0;
}