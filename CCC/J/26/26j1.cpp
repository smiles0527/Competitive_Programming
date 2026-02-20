#include <bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int b, t, p; cin >> b >> t >> p;
	if(t - p - b > 0) cout << "Y " << t-p-b;
	else cout << 'N';
}
