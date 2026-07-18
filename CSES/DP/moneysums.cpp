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
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n; cin >> n;
	vector<int> x(n);
	int S = 0;
	for(auto &x : x){ cin >> x; S += x;};

	bitset<100001> reach;
	reach[0] = 1;
	for(int v : x) reach |= reach << v;

	vector<int> ans;
	for(int s=1; s<=S; s++) if(reach[s]) ans.push_back(s);


	cout<<ans.size()<<'\n';
	for(int i=0; i<(int)ans.size();i++){
		cout<<ans[i]<<" \n"[i+1==(int)ans.size()];
	}

	return 0;
}	