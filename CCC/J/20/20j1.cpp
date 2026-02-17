#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int s, m, l; cin >> s >> m >> l;

	if(s + 2*m + 3*l >= 10){
		cout << "happy";
		return 0;
	}

	cout << "sad";

}
