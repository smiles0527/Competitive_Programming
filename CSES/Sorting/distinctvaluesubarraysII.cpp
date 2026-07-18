#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, k; cin >> n >> k;
	vector<ll> a(n); for(auto &x : a) cin >> x;

	unordered_map<ll, int> freq;
	freq.reserve((size_t)n*2);
	freq.max_load_factor(0.7f);

	ll ans = 0;
	int distinct = 0;
	int l = 0;

	for(int r = 0; r < n; r++){
		int &fr = freq[a[r]];
		if(fr==0) distinct++;
		fr++;

		while(distinct > k){
			int &fl = freq[a[l]];
			fl--;
			if(fl == 0) distinct--;
			l++;
		}
		ans += (ll)(r-l+1);
	}
	cout << ans;
}
