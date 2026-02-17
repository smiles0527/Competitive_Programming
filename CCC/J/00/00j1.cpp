#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int a, b; cin >> a >> b;

	cout << "Sun Mon Tue Wed Thr Fri Sat\n";
	int pos = 1;
	for(int i = 1; i < a; i++){
		cout << "    "; 
		pos++;
	}

	for(int d = 1; d <= b; d++){
		cout << setw(3) << d;
		if(pos % 7 != 0 && d != b) cout << ' ';
		if(pos % 7 ==0) cout << '\n';
		pos++;
	}
	if((pos-1)%7!=0) cout << '\n';
}
