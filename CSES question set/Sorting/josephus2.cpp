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
ll k;
int N;
int bit[200005];
int LOGN;
void upd(int i, int v){ for(; i <= n; i += i & -i) bit[i] += v; }
int findkth(int j){                              // smallest index with prefix sum == j
	int pos = 0;
	for(int pw = LOGN; pw >= 0; pw--){
		int nx = pos + (1 << pw);
		if(nx <= n && bit[nx] < j){ pos = nx; j -= bit[nx]; }
	}
	return pos + 1;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> k;
	LOGN = 0; while((1 << (LOGN+1)) <= n) LOGN++;
	for(int i = 1; i <= n; i++) upd(i, 1);
	int m = n;
	int idx = 0;                                 // 0-based pointer among survivors
	vector<int> out; out.reserve(n);
	for(int step = 0; step < n; step++){
		idx = (int)(((ll)idx + k) % m);          // 0-based victim index
		int child = findkth(idx + 1);            // (idx+1)-th alive child
		out.pb(child);
		upd(child, -1);
		m--;
		// pointer now references the child after the removed one, still at 'idx'
		// but if idx == m (removed last in current ordering), wrap to 0
		if(m > 0) idx %= m;
	}
	for(int i = 0; i < n; i++) cout << out[i] << (i+1 == n ? '\n' : ' ');
	return 0;
}