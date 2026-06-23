#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int MOD = 1e9+7;
int n;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	vector<ii> task(n);                          // {duration, deadline}
	for(int i = 0; i < n; i++){
		ll a, d; cin >> a >> d;
		task[i] = {a, d};
	}
	sort(task.begin(), task.end());              // ascending duration
	ll t = 0, reward = 0;
	for(auto &tk : task){
		t += tk.f;                               // finishing time after this task
		reward += tk.s - t;                      // d - f
	}
	cout << reward << '\n';
	return 0;
}