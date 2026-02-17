#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int a, b, c, d; cin >> a >> b >> c >> d;
	
	int ba[] = {461, 431, 420, 0};
	int s[] = {100, 57, 70, 0};
	int da[] = {130, 160, 118, 0};
	int de[] = {167, 266, 75, 0};

	cout << "Your total Calorie count is " << ba[a-1] + s[b-1] + da[c-1] + de[d-1] << ".";

}
