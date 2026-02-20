#include <bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	vector<int> a(5); for(int &x : a) cin >> x;
    int d; cin >> d;
    sort(a.begin(), a.end());
    a.pop_back();
    a.erase(a.begin());
    cout << accumulate(a.begin(), a.end(), 0) * d;
}