#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define for(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int lim, speed; cin >> lim >> speed;
	if(speed <= lim){ cout << "Congratulations, you are within the speed limit!"; return 0;}

	int fine = speed - lim;
	if(fine < 21) cout << "You are speeding and your fine is $100.";
	else if(fine <31) cout << "You are speeding and your fine is $270.";
	else cout << "You are speeding and your fine is $500.";

}
