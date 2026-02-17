#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define for(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int month, day; cin >> month >> day;
	
	if(month < 2) cout << "Before";
	else if (month > 2) cout << "After";
	else{
		if(day < 18) cout << "Before";
		else if(day > 18) cout << "After";
		else cout << "Special";
	}
	return 0;
	
}
