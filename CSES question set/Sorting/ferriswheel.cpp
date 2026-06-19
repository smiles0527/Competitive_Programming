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
	vector<int> p(n);
	for(auto &v : p) cin >> v;
	sort(p.begin(), p.end());
	int i = 0, j = n - 1, cnt = 0;
	while(i <= j){
		if(p[i] + p[j] <= x) i++;                // seat lightest with heaviest
		j--;                                     // heaviest always takes the gondola
		cnt++;
	}
	cout << cnt << '\n';
	return 0;
}