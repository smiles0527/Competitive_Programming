#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int m, n; cin >> m >> n;
	int ways = 0;

	for(int a = 1; a <= m; a++){
		int b = 10 - a;
		if(1 <= b && b <= n) ways++;
	}

	if(ways==1) cout << "There is 1 way to get the sum 10.\n";
	else cout << "There are " << ways<< " ways to get the sum 10.\n";
		
}
