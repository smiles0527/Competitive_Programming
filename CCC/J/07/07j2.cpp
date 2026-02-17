#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	unordered_map<string, string> t = {
		{"CU", "see you"},
		{":-)", "I'm happy"},
		{":-(", "I'm unhappy"},
		{";-)", "wink"},
		{":-P", "stick out my tongue"},
		{"(~.~)", "sleepy"},
		{"TA", "totally awesome"},
		{"CCC", "Canadian Computing Competition"},
		{"CUZ", "because"},
		{"TY", "thank-you"},
		{"YW", "you're welcome"},
		{"TTYL", "talk to you later"}
	};
	string s;
	while(cin >> s){
		auto it = t.find(s);
		if(it != t.end()) cout << it->second << '\n';
		else cout << s << '\n';
		if(s == "TTYL") break;
	}
	return 0;		
}
