#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
		
	int n; cin >> n;

	int cnt = 0;
	for(int i = 0; i < n; i++){
		int p, f; 
		cin >> p >> f;
		int r = 5*p - 3*f;
		if(r>40) cnt++;
	}
	
	cout << cnt;
	if(cnt == n) cout << "+";

}
