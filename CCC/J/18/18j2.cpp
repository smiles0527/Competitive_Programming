#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n; cin >> n;
	string y, t; cin >> y >> t;

	int cnt = 0;
	for(int i = 0; i < n; i++)
		if(y[i]=='C' && t[i]=='C') cnt++;
	
	cout << cnt;

}
