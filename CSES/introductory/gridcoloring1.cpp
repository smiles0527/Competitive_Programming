#include <bits/stdc++.h>
using namespace std;
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
