#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	

	int a,b,c;cin>>a>>b>>c;cout<<a+b+c-min({a,b,c})-max({a,b,c});	
}
