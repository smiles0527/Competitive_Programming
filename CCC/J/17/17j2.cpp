#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, k; cin >> n >> k;
	ll sum = 0;

	for(int i = 0; i <= k; i++){
		sum += n;
		n*=10;
	}
	
	cout << sum;
}
