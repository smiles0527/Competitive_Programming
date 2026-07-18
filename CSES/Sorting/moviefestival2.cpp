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
int n, k;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> k;
	vector<ii> mv(n);                            // {end, start}
	for(int i = 0; i < n; i++){
		ll a, b; cin >> a >> b;
		mv[i] = {b, a};
	}
	sort(mv.begin(), mv.end());                  // by end time

	multiset<ll> ends;                           // k members' last-watched end times
	for(int i = 0; i < k; i++) ends.insert(0);

	int cnt = 0;
	for(auto &m : mv){
		ll b = m.f, a = m.s;
		auto it = ends.upper_bound(a);           // first end > start
		if(it == ends.begin()) continue;         // no member free by start
		--it;                                    // largest end <= start
		ends.erase(it);
		ends.insert(b);
		cnt++;
	}
	cout << cnt << '\n';
	return 0;
}