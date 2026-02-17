#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int h; cin >> h;
	int half = h/2;

	for(int i = 0; i < half; i++){
		int stars = 2*i+1;
		int spaces = 2*(h-stars);
		cout << string(stars, '*') << string(spaces, ' ') << string(stars, '*') << '\n';
	}
	cout << string(2*h, '*') << '\n';

	for(int i = half-1; i >=0; i--){
		int stars = 2*i+1;
		int spaces = 2*(h-stars);
		cout << string(stars, '*') << string(spaces, ' ') << string(stars, '*') << '\n';
	}
	return 0;
}
