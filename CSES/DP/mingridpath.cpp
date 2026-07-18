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
	
	int n; cin >> n;
	vector<string> g(n); for(auto &x : g) cin >> x;

	string res; res.reserve(2*n-1);		
	vector<char> alive(n,0); alive[0]=1; res += g[0][0];

	for(int i = 1; i <= 2*n-2; i++){
		int lo = max(0, i-(n-1)), hi = min(i, n-1);
		char best = 'Z'+1;
		//pass1
		for(int x=lo;x<=hi;x++){
			int j=i-x;
			bool reach = (x>0 && alive[x-1]) || alive[x];
			if(reach) best = min(best, g[x][j]);
		}
		res += best;
		//pass2
		vector<char>nxt(n,0);
		for(int x=lo;x<=hi;x++){
			int j=i-x;
			bool reach = (x>0 && alive[x-1]) || alive[x];
			nxt[x] = (reach && g[x][j]==best);
		}
		alive.swap(nxt);
	}
	
	cout<<res<<'\n';
	return 0;
}	