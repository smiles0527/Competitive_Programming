#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int d, e, w; cin >> d >> e >> w;
	double ca = 0.25 * max(0, d-100) + 0.15*e + 0.20*w;
	double cb = 0.45 * max(0, d-250) + 0.35*e + 0.25*w;

	cout << fixed << setprecision(2);
	cout << "Plan A costs " << ca << '\n';
	cout << "Plan B costs " << cb << '\n';

	if(ca < cb) cout << "Plan A is cheapest.";
	else if(cb < ca) cout << "Plan B is cheapest.";
	else cout << "Plan A and B are the same price.";
	
}
