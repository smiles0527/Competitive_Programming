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

	ll n; cin >> n;
 
	int limit = 1 << n;
	for(int i = 0; i < limit; i++){
		int g = i ^ (i >> 1);
		for(int b = n-1; b>=0; b--){
			cout << ((g>>b) & 1);
		}
		cout << '\n';
	}
	return 0;
}