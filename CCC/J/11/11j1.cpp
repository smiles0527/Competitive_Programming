#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int a, e; cin >> a >> e;
	if(a >= 3 && e <= 4) cout << "TroyMartian\n";
	if(a <= 6 && e >=2) cout << "VladSaturnian\n";
	if(a <= 2 && e <=3) cout << "GraemeMercurian\n";

}
