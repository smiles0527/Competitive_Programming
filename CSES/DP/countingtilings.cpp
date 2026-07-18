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

int n,m;
ll dp[1024], nd[1024];

void go(int j, int c, int nx){
	if(j==n){ nd[nx]=(nd[nx]+dp[c])%MOD; return;}
	if(c>>j & 1){ go(j+1,c,nx); return;} //alr covered
	if(j+1<n && !(c>>(j+1)&1)) go(j+2,c,nx); //vertical
	go(j+1,c,nx | (1<<j)); //horizontal pertrudes
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> n >> m;
	dp[0]=1;
	for(int col=0;col<m;col++){
		for(int k=0; k<(1<<n);k++) nd[k]=0;
		for(int c=0; c<(1<<n);c++) if(dp[c]	) go(0,c,0);
		for(int k=0; k<(1<<n);k++) dp[k]=nd[k];
	}
	cout << dp[0];
	return 0;
}