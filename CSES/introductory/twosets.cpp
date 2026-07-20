#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	ll n; cin >> n;
	if(n*(n+1)/2 %2){
		cout << "NO";
		return 0;
	}
	
	vector<int> A, B;
	
	if(n%4==0){
		for(int a=1;a<=n;a+=4){
			A.push_back(a);
			A.push_back(a+3);
			B.push_back(a+1);
			B.push_back(a+2);
		}
	} else{
		A = {1, 2}; B = {3};
		for(int i=4;i<=n;i+=4){
			A.push_back(i);
			A.push_back(i+3);
			B.push_back(i+1);
			B.push_back(i+2);
		}
	}
 
	cout << "YES\n";
	cout << A.size() << '\n';
	for(int x : A) cout << x << ' ';
	cout << '\n';
	cout << B.size() << '\n';
	for(int x : B) cout << x << ' ';


	return 0;
}
