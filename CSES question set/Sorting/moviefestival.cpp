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
	vector<ii> mv(n);
	for(int i = 0; i < n; i++){
		int a, b;
		cin >> a >> b;
		mv[i] = {b, a};                          // sort by end time
	}
	sort(mv.begin(), mv.end());
	int cnt = 0, end = 0;
	for(auto &m : mv){
		if(m.s >= end){ cnt++; end = m.f; }      // start >= last end
	}
	cout << cnt << '\n';
	return 0;
}