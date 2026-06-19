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
	vi a(n), d(n);
	ll T = 0;
	for(int i=0;i<n;i++){cin >> a[i]; T += a[i]; d[i] = a[i];}

	for(int L = 1; L < n; L++){ //seglen 1 ... L+1 extend
		for(int i = 0; i + L < n; i++){
			d[i] = max(a[i]-d[i+1], a[i+L]-d[i]);
		}
	}

	cout << (T +d[0]) / 2 << '\n';
	return 0;
}	