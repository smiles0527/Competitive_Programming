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
	multiset<int> tops;                          // current top size of each tower
	for(int i = 0, k; i < n; i++){
		cin >> k;
		auto it = tops.upper_bound(k);           // smallest top strictly > k
		if(it == tops.end()) tops.insert(k);     // no fit -> new tower
		else { tops.erase(it); tops.insert(k); } // place on that tower, update top
	}
	cout << tops.size() << '\n';
	return 0;
}