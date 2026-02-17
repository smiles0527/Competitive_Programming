#include <bits/stdc++.h>
using namespace std;
#define ll long long

bool vowel(char c){
	return c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||c=='y';
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	while(cin >> s){
		if(s == "quit!") break;

		int n = (int)s.size();
		if(n>4 && s[n-2]=='o' && s[n-1]=='r' && !vowel(s[n-3])){
			s.insert(n-1, "u");
		}
		cout << s << '\n';
	}	
}
