#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int lo, hi; cin >> lo >> hi;
	int cnt = 0;

	for(int i = lo; i <= hi; i++){
		int d = 0;
		for(int j = 1; j <= i; j++){
			if(i%j==0)d++;
		}
		if(d==4)cnt++;
	}
	cout << "The number of RSA numbers between " << lo << " and " << hi << " is " << cnt;
}
