#include <bits/stdc++.h>
using namespace std;
#define ll long long
using i128 = __int128_t;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, l, q; cin >> n >> l >> q;
	vector<int> d(n+2);//wtf it disapeard
	while(l--){
		int p, s; cin >> p >> s;
		int l = max(1, p-s); int r = min(n,p+s);
		d[l]++; d[r+1]--;
	}
	for(int i = 1; i<=n; i++) d[i]+=d[i-1];

	while(q--){
		int x; cin >> x;
		cout << (d[x] > 0 ? 'Y' : 'N') << '\n'; 
	}

}