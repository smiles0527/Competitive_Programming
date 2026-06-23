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
	vector<int> t;
	for(int i=0,x;i<n;i++){
		cin>>x;
		auto it=lower_bound(t.begin(),t.end(),x);
		if(it==t.end())t.push_back(x);
		else *it=x;
	}
	cout << t.size()<<'\n';

	return 0;
}
