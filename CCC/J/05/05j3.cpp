#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
		
	vector<string> t, s;
	string x;

	while(cin >> x){
		t.push_back(x);
		cin >> x;
		s.push_back(x);
	}
		
	auto flip = [&](const string& t){
		return (t == "L") ? "RIGHT" : "LEFT";
	};
	
	for(int i = (int)t.size()-2; i >= 0; i--){
		cout << "Turn " << flip(t[i+1]) << " onto " << s[i] << " street.\n";
	}

	cout << "Turn " << flip(t[0]) << " into your HOME.\n";
	return 0;
}	

