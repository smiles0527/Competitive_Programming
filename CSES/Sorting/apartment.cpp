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
int n, m, k;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> k;
	vector<int> a(n), b(m);
	for(auto &x : a) cin >> x;
	for(auto &x : b) cin >> x;
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	int i = 0, j = 0, cnt = 0;
	while(i < n && j < m){
		if(b[j] < a[i] - k) j++;                 // apartment too small
		else if(b[j] > a[i] + k) i++;            // too big for this applicant
		else { cnt++; i++; j++; }                // match
	}
	cout << cnt << '\n';
	return 0;
}