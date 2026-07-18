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
	vector<array<int,3>> r(n);                   // {x, y, idx}
	for(int i = 0; i < n; i++){
		int x, y; cin >> x >> y;
		r[i] = {x, y, i};
	}
	vector<int> contains(n, 0), contained(n, 0);

	// contained-by-another: sort x asc, y desc; running max y over earlier (x' <= x)
	sort(r.begin(), r.end(), [](const array<int,3>& a, const array<int,3>& b){
		if(a[0] != b[0]) return a[0] < b[0];
		return a[1] > b[1];
	});
	int maxY = INT_MIN;
	for(int i = 0; i < n; i++){
		if(maxY >= r[i][1]) contained[r[i][2]] = 1;   // earlier range with x'<=x, y'>=y
		maxY = max(maxY, r[i][1]);
	}

	// contains-another: same order, scan from end; min y over later (x' >= x)
	int minY = INT_MAX;
	for(int i = n-1; i >= 0; i--){
		if(minY <= r[i][1]) contains[r[i][2]] = 1;    // later range with x'>=x, y'<=y
		minY = min(minY, r[i][1]);
	}

	for(int i = 0; i < n; i++) cout << contains[i] << (i+1==n?'\n':' ');
	for(int i = 0; i < n; i++) cout << contained[i] << (i+1==n?'\n':' ');
	return 0;
}