#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    int n;
	while(cin >> n && n !=0){
		int a; 
		for(a=1; a*a<=n;a++);
		for(a--; n%a!=0; a--);
		
		int b = n/a;
		int p = 2*(a+b);

		int x = min(a,b), y=max(a,b);
		cout << "Minimum perimeter is " << p << " with dimensions " << x << " x " << y << '\n';
	}
}