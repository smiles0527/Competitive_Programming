#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string s; cin >> s;
	string ok = "IOSHZXN";

	for(char c : s){
		if(ok.find(c) == string::npos){
			cout << "NO\n";
			return 0;
		}
	}
	cout << "YES\n";

}
