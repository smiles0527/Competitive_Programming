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
	vector<ll> a(n);
	for(auto &v : a) cin >> v;
	ll sum = 0, cnt = 0;
	int l = 0;
	for(int r = 0; r < n; r++){
		sum += a[r];
		while(sum > x) sum -= a[l++];            // shrink (safe: positives)
		if(sum == x) cnt++;
	}
	cout << cnt << '\n';
	return 0;
}