#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int a, b, c, d, e, f;
	cin >> a >> b >> c >> d >> e >> f;
	ll t1=3*a+2*b+c; ll t2 = 3*d+2*e+f;
	if(t1<t2) {cout << 'B'; return 0;}
	else if(t1 == t2) { cout << 'T'; return 0;}
	cout << 'A';	
}
