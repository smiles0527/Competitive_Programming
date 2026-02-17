#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int x, y; cin >> x >> y;	
	for(int i = x; i <= y; i+=60){
		cout << "All positions change in year " << i << '\n';
	}
	
}
