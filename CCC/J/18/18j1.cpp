#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
		
	int a, b, c, d;
	cin >> a >> b >> c >> d;
		
	if((a == 8 || a == 9) && (d == 8 || d == 9) && b == c){
		cout << "ignore";
		return 0;
	}

	cout << "answer";
	
}
