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
void solve(int n, int a, int b, int c){
	if(!n) return;
	solve(n-1, a, c, b);
	cout << a << ' ' << c << '\n';
	solve(n-1, b, a, c);
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
 
	int n; cin >> n;
 
	cout << (1LL << n) - 1 << '\n';
	solve(n, 1, 2, 3);
}