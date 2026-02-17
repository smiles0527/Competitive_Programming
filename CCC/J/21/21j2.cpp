#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
		
	int x; cin >> x;
	string n, w;
	int b, mb = -1;
	for(int i = 0; i < x; i++){
		cin >> n >> b;
		if(b > mb){
			mb = b;
			w = n;
		}
	}
	cout << w;
}
