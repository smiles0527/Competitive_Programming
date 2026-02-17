#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	double weight, height; cin >> weight >> height;
	double bmi = (double)weight / (height * height);
	if(bmi < 18.5) cout << "Underweight";
	else if (bmi <= 25.0) cout << "Normal weight";
	else cout << "Overweight";

	return 0;

}
