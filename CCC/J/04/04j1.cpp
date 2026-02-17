#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n; cin >> n; int s = 0; while((s+1)*(s+1)<=n)s++; cout << "The largest square has side length " << s << ".\n"; return 0;
	
}
