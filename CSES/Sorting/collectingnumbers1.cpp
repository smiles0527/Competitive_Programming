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
int pos[200005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; i++){
		int x; cin >> x;
		pos[x] = i;
	}
	int rounds = 1;
	for(int v = 1; v < n; v++)
		if(pos[v+1] < pos[v]) rounds++;          // v+1 is left of v -> new pass
	cout << rounds << '\n';
	return 0;
}