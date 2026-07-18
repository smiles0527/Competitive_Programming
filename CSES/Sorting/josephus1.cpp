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
	queue<int> q;
	for(int i = 1; i <= n; i++) q.push(i);
	vector<int> out;
	out.reserve(n);
	while(!q.empty()){
		q.push(q.front()); q.pop();              // skip one
		out.pb(q.front()); q.pop();              // remove next
	}
	for(int i = 0; i < n; i++) cout << out[i] << (i+1 == n ? '\n' : ' ');
	return 0;
}