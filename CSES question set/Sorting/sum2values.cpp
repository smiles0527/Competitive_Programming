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
int n, x;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> x;
	unordered_map<int,int> seen;
	seen.reserve(2*n);
	for(int i = 1; i <= n; i++){
		int a; cin >> a;
		int need = x - a;
		auto it = seen.find(need);
		if(it != seen.end()){
			cout << it->s << ' ' << i << '\n';
			return 0;
		}
		seen.emplace(a, i);                      // record current value's index
	}
	cout << "IMPOSSIBLE\n";
	return 0;
}