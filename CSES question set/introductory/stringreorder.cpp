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
	
	string s; cin >> s;
	int n = (int)s.size();
 
	array<int, 26> cnt{};
	for(char ch : s) cnt[ch - 'A']++;
 
	int mx0 = 0;
	for(int v : cnt) mx0 = max(mx0, v);
	if(mx0 > (n+1)/2){
		cout << -1 << '\n';
		return 0;
	}
	string out; out.reserve(n);
	int prev = -1;
 
	for(int i = 0; i < n; i++){
		bool ok = false;
		for(int x = 0; x < 26; x++){
			if(x == prev || cnt[x] == 0) continue;
			cnt[x]--;
			int L = n - i - 1;
			bool good = true;
			if(L > 0){
				int cx = cnt[x];
				if(L - cx == 0) good = false;
				int mx = 0;
				for(int v : cnt) mx = max(mx, v);
				int CH = (L + 1) / 2;
				if(mx > CH) good = false;
				if((L&1) && cx == CH) good = false;
			}
			if(good){
				out.push_back(char('A' + x));
				prev = x;
				ok = true;
				break;
			}
			cnt[x]++;
		}
		if(!ok){
			cout << -1 << '\n'; return 0;
		}
	}
	cout << out << '\n'; 
	return 0;
}