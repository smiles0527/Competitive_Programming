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
	if(n == 1){ cout << "01\n"; return 0; }
	int nodes = 1 << (n-1);
	int mask = nodes - 1;
	vector<int> it_(nodes, 0);
	vector<int> stk; stk.pb(0);
	vector<int> edgebit; edgebit.pb(-1);
	string seq;
	while(!stk.empty()){
		int v = stk.back();
		if(it_[v] < 2){
			int b = it_[v]++;
			int u = ((v << 1) | b) & mask;
			stk.pb(u);
			edgebit.pb(b);
		} else {
			if(edgebit.back() != -1) seq.pb('0' + edgebit.back());
			stk.pop_back();
			edgebit.pop_back();
		}
	}
	reverse(seq.begin(), seq.end());        // 2^n edge labels = cyclic De Bruijn
	string res = seq + seq.substr(0, n-1);  // linearize: append first n-1 labels
	cout << res << '\n';
	return 0;
}