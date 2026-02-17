#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int x, y; cin >> x >> y;

	if(x > 0 && y > 0) cout << 1;
	else if(x < 0 && y > 0) cout <<2;
	else if(x < 0 && y < 0) cout  << 3;
	else cout << 4;


}