#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int b, c; cin >> b >> c;
	int p = 5*b-400;
	
	cout << p << '\n';
	if(p>100) cout << -1;
	else if(p==100) cout << 0;
	else cout << 1;
	
}
