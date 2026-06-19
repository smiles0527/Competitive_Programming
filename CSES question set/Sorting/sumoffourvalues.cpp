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
ll x;
struct H {
	size_t operator()(ll k) const {
		k += 0x9e3779b97f4a7c15ULL;
		k = (k ^ (k >> 30)) * 0xbf58476d1ce4e5b9ULL;
		k = (k ^ (k >> 27)) * 0x94d049bb133111ebULL;
		return k ^ (k >> 31);
	}
};
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> x;
	vector<ll> a(n);
	for(auto &v : a) cin >> v;

	unordered_map<ll, pair<int,int>, H> sp;
	sp.reserve(n*(n-1)/2 + 16);
	sp.max_load_factor(0.5);
	for(int k = 2; k < n; k++){
		for(int i = 0; i < k-1; i++)
			sp.emplace(a[i] + a[k-1], make_pair(i, k-1));   // pairs with larger index = k-1
		for(int l = k + 1; l < n; l++){
			auto it = sp.find(x - a[k] - a[l]);
			if(it != sp.end()){
				cout << it->s.first+1 << ' ' << it->s.second+1 << ' ' << k+1 << ' ' << l+1 << '\n';
				return 0;
			}
		}
	}
	cout << "IMPOSSIBLE\n";
	return 0;
}