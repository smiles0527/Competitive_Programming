#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int a, b, c, total; cin >> a >> b >> c >> total;
	
	int ways = 0;
	for(int t = 0; t*a <= total; t++){
		for(int p = 0; t*a+p*b <= total; p++){
			for(int y = 0; t*a+p*b+y*c <= total; y++){
				if(t==0 && p==0 && y==0) continue;
				cout << t << " Brown Trout, " << p << " Northern Pike, " << y << " Yellow Pickerel\n";
				ways ++;
			}
		}
	}
	cout << "Number of ways to catch fish: " << ways;
}
