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
int n, m;
int bit[200005];
void upd(int i, int v){ for(; i <= m; i += i & -i) bit[i] += v; }
int qry(int i){ int r = 0; for(; i > 0; i -= i & -i) r += bit[i]; return r; }
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	vector<array<int,3>> r(n);
	vector<int> ys;
	for(int i = 0; i < n; i++){
		int x, y; cin >> x >> y;
		r[i] = {x, y, i};
		ys.pb(y);
	}
	sort(ys.begin(), ys.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end());
	m = ys.size();
	auto yid = [&](int y){ return int(lower_bound(ys.begin(), ys.end(), y) - ys.begin()) + 1; };

	sort(r.begin(), r.end(), [](const array<int,3>& a, const array<int,3>& b){
		if(a[0] != b[0]) return a[0] < b[0];
		return a[1] > b[1];
	});

	vector<int> contains(n, 0), contained(n, 0);

	// forward: earlier ranges have x'<=x; current is contained by those with y'>=y
	for(int i = 0; i < n; i++){
		int id = yid(r[i][1]);
		contained[r[i][2]] = qry(m) - qry(id - 1);
		upd(id, 1);
	}
	for(int i = 1; i <= m; i++) bit[i] = 0;

	// reverse: later ranges have x'>=x; current contains those with y'<=y
	for(int i = n-1; i >= 0; i--){
		int id = yid(r[i][1]);
		contains[r[i][2]] = qry(id);
		upd(id, 1);
	}

	for(int i = 0; i < n; i++) cout << contains[i] << (i+1==n?'\n':' ');
	for(int i = 0; i < n; i++) cout << contained[i] << (i+1==n?'\n':' ');
	return 0;
}