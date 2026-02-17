#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	vector<vector<int>> a(4, vector<int>(4));;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			cin >> a[i][j];
		}
	}
	int x = 0;
	for(int i = 0; i < 4; i++) x += a[0][i];

	for(int i = 0; i < 4; i++){
		int rs = 0;
		for(int j = 0; j < 4; j++) rs += a[i][j];
		if(rs != x){
			cout << "not magic\n";
			return 0;
		}
	}

	for(int j = 0; j < 4; j++){
		int cs = 0;
		for(int i = 0; i < 4; i++) cs += a[i][j];
		if(cs != x){
			cout << "not magic\n";
			return 0;
		}
	}
	cout << "magic\n";
}
