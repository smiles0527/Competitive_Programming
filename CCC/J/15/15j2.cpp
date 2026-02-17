#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string s; getline(cin, s);
	int happy = 0, sad = 0;
	for(int i = 0; i+2 < (int)s.size(); i++){
		if(s.substr(i,3) == ":-)")happy++;
		if(s.substr(i,3) == ":-(")sad++;
	}
	if(happy == 0 && sad == 0) cout << "none";
	else if (happy == sad) cout << "unsure";
	else if (happy > sad) cout << "happy";
	else cout << "sad";

}
