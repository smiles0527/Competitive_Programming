#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int v; cin >> v;
	string s; cin >> s;
	int a = 0, b = 0;
	for(char c : s){
		if(c=='A') a++;
		else b++;
	}
	if(a>b) cout << "A\n";
	else if(b>a) cout << "B\n";
	else cout << "Tie\n";

}
