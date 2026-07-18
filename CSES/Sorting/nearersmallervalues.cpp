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
	vector<int> x(n);
	for(auto &v : x) cin >> v;
	vector<int> st;                              // stack of indices, increasing values
	for(int i = 0; i < n; i++){
		while(!st.empty() && x[st.back()] >= x[i]) st.pop_back();
		int ans = st.empty() ? 0 : st.back() + 1;   // 1-based, 0 if none
		cout << ans << (i+1 == n ? '\n' : ' ');
		st.pb(i);
	}
	return 0;
}