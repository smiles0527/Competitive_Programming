#include <bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string n; cin >> n;
 
	sort(n.begin(), n.end());
 
	vector<string> ans;
	do ans.push_back(n);
	while(next_permutation(n.begin(), n.end()));
 
	cout << ans.size() << '\n';
	for(auto &x : ans) cout << x << '\n';
	return 0;
}
