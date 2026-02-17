#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int x, m; cin >> x >> m;
	for(int i = 1; i < m; i++){
		if((x*i)%m == 1){
			cout << i << '\n';
			return 0;
		}
	}
	cout << "No such integer exists.\n";
}
