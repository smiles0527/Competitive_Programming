#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int h, m; cin >> h >> m;
	for(int i = 1; i <= m; i++){
		int A = -6 * pow(i,4) + h * pow(i,3) + 2 * pow(i, 2) + i;
		if(A <= 0){
			cout << "The balloon first touches ground at hour:\n";
			cout << i << '\n';
			return 0;
		}
	}

	cout << "The balloon does not touch ground in the given time.";
}
