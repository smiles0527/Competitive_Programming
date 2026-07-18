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

	string n; cin >> n;
 
	sort(n.begin(), n.end());
 
	vector<string> ans;
	do ans.push_back(n);
	while(next_permutation(n.begin(), n.end()));
 
	cout << ans.size() << '\n';
	for(auto &x : ans) cout << x << '\n';
	return 0;
}