#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n; cin >> n;
 
	int limit = 1 << n;
	for(int i = 0; i < limit; i++){
		int g = i ^ (i >> 1);
		for(int b = n-1; b>=0; b--){
			cout << ((g>>b) & 1);
		}
		cout << '\n';
	}
	return 0;
}
