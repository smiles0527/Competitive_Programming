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
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    string out;
    out.reserve(1 << 20);
    while (t--) {
        int n; cin >> n;
        bool anyOdd = false;
        for (int i = 0; i < n; i++) {
            int v; cin >> v;
            if (v & 1) anyOdd = true;
        }
        out += (anyOdd ? "first" : "second");
        out += '\n';
    }
    cout << out;
    return 0;
}