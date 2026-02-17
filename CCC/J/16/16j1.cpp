#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int cnt = 0;
	for(int i = 0; i < 6; i++){
		char a; cin >> a;
		if(a == 'W') cnt++;
	}	
	if(cnt >= 5) cout << 1;
	else if (cnt >= 3) cout << 2;
	else if (cnt >= 1) cout << 3;
	else cout << -1;
	
}
