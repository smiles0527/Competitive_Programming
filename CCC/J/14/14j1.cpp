#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define for(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
		
	int a, b, c; cin >> a >> b >> c;	
	if(a+b+c != 180){ cout << "Error"; return 0;}
	else{
		if(a == b && b == c) cout << "Equilateral";
		else if(a == b || a == c || b == c) cout << "Isosceles";
		else cout << "Scalene";
	}
}
