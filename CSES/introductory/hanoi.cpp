#include <bits/stdc++.h>
using namespace std;
void solve(int n, int a, int b, int c){
	if(!n) return;
	solve(n-1, a, c, b);
	cout << a << ' ' << c << '\n';
	solve(n-1, b, a, c);
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
 
	int n; cin >> n;
 
	cout << (1LL << n) - 1 << '\n';
	solve(n, 1, 2, 3);
}
