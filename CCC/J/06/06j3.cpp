#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	
	string key = "22233344455566677778889999";
	string press = "12312312312312312341231234";

	string s; 
	while(cin >> s && s != "halt"){
		int t = 0;
		for(int i = 0; i < (int)s.size(); i++){
			int a = s[i] - 'a';
			if(i && key[a] == key[s[i-1]-'a']){
				t+=2;
			}
			t += (press[a]-'0');
		}
		cout << t << '\n';
	}
	
}	

