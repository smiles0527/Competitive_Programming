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
	if(n==1){ cout << 1; return 0;}
	if(n==3 || n ==2){cout << "NO SOLUTION"; return 0;}
	
	for(int i=2;i<=n;i+=2) cout << i << ' ';
	for(int i=1;i<=n;i+=2) cout << i << (i + 2 <= n ? ' ': '\n');

	return 0;
}