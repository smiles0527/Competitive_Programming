#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int a, b, c, d, s; cin >> a >> b >> c >> d >> s;
	int nikky = 0, byron = 0;
	int nc = a+b, bc = c+d;

	for(int i = 1; i <= s; i++){
		int nr = (i-1) % nc;
		if(nr < a) nikky++;
		else nikky--;

		int br = (i-1) % bc;
		if(br < c) byron++;
		else byron--;
	}

	if(nikky>byron) cout << "Nikky\n";
	else if (byron > nikky) cout << "Byron\n";
	else cout << "Tied\n";	
	
}
