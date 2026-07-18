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
	
	int n, m; cin >> n >> m;
	
	vector<string> s(n);
	for(int i = 0; i < n; i++) cin >> s[i];
 
	vector<string> out(n, string(m, 'A'));
 
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			char old = s[i][j];
			if(((i+j)&1) == 0){
				out[i][j] = (old == 'A' ? 'B' : 'A');
			} else{
				out[i][j] = (old == 'C' ? 'D' : 'C');
			}
		}
	}
	for(auto &x : out) cout << x << '\n';
	return 0;
}