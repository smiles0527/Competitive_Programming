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
	vector<int> p(n);
	for(auto &v : p) cin >> v;
	sort(p.begin(), p.end());
	ll med = p[n/2];
	ll cost = 0;
	for(int v : p) cost += llabs((ll)v - med);
	cout << cost << '\n';
	return 0;
}