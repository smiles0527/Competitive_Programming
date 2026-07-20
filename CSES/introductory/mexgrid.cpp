#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	ll n; cin >> n;
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(j) cout << ' ';
			cout << (i^j);
		}
		cout << '\n';
	}
	return 0;
}
