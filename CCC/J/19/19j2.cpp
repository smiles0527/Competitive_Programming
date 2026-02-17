#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int l; cin >> l;
	for(int i = 0; i < l; i++){
		int n; char ch; 
		cin >> n >> ch;
		cout << string(n, ch) << '\n';
	}

}
