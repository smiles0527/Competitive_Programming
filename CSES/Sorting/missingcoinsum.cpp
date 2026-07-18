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
int n;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	vector<int> x(n);
	for(auto &v : x) cin >> v;
	sort(x.begin(), x.end());
	ll reach = 0;
	for(int v : x){
		if((ll)v > reach + 1) break;             // gap at reach+1
		reach += v;
	}
	cout << reach + 1 << '\n';
	return 0;
}