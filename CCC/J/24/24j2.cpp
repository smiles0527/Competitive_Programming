#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

	int d; cin >> d;
	while(true){
		int y; cin >> y;
		if(d > y) d += y;
		else{
			cout << d; 
			return 0;
		}
	}

}
