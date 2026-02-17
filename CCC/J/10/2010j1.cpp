#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n; cin >> n;
	int ans = 0;
	for(int i = 0; i <= 5; i++){
		int b = n-i;
		if(0<=b && b<=5 && i >=b) ans++;
	}

	cout << ans;

}
