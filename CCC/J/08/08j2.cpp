#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	deque<char> p = {'A','B','C','D','E'};
	while(true){
		int b, n; cin >> b >> n;
		if(b==4){
			for(int i = 0; i < 5; i++){
				if(i)cout << ' ';
				cout << p[i];
			}
			cout << '\n';
			break;
		}
	
		n%=5;
		if(b==1){
			while(n--){
				char x = p.front();
				p.pop_front();
				p.push_back(x);
			}
		} else if(b==2){
			while(n--){
				char x = p.back();
				p.pop_back();
				p.push_front(x);
			}
		} else if(b==3){
			if(n%2==1) swap(p[0], p[1]);
		}
	}
}
