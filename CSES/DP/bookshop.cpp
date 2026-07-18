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
	
	int n, x; cin >> n >> x;
	vector<int> h(n), s(n);
	for(auto &x : h) cin >> x;
	for(auto &x : s) cin >> x;

	vector<int> dp(x+1,0); 
	for(int i=0;i<n;i++){
		for(int b=x;b>=h[i];b--){
			dp[b]=max(dp[b], dp[b-h[i]]+s[i]);
		}
	}
	cout << dp[x];
	return 0;
}