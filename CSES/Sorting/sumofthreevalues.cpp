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
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> x;
	vector<ii> a(n);                             // {value, original index}
	for(int i = 0; i < n; i++){
		ll v; cin >> v;
		a[i] = {v, i + 1};
	}
	sort(a.begin(), a.end());
	for(int i = 0; i < n; i++){
		ll need = x - a[i].f;
		int l = i + 1, r = n - 1;
		while(l < r){
			ll sum = a[l].f + a[r].f;
			if(sum == need){
				cout << a[i].s << ' ' << a[l].s << ' ' << a[r].s << '\n';
				return 0;
			}
			if(sum < need) l++;
			else r--;
		}
	}
	cout << "IMPOSSIBLE\n";
	return 0;
}