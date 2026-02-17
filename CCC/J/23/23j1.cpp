#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int p, c; cin >> p >> c;
	cout << 50*p-10*c+(p>c?500:0);
		
}
