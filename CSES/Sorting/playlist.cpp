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
	vector<int> k(n);
	for(auto &v : k) cin >> v;
	unordered_map<int,int> last;
	last.reserve(2*n);
	int l = 0, best = 0;
	for(int r = 0; r < n; r++){
		auto it = last.find(k[r]);
		if(it != last.end() && it->s >= l) l = it->s + 1;   // shrink past duplicate
		last[k[r]] = r;
		best = max(best, r - l + 1);
	}
	cout << best << '\n';
	return 0;
}