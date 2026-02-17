#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

	map<string, int> shu = {
		{"Poblano", 1500},
		{"Mirasol", 6000},
		{"Serrano", 15500},
		{"Cayenne", 40000},
		{"Thai", 75000},
		{"Habanero", 125000}
	};
		
	int n; cin >> n;
	int total = 0;
	while(n--){
		string p; cin >> p;
		total += shu[p];
	}	
	cout << total;
}
