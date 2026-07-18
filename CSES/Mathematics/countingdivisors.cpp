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
const int V = 1000000;
int spf[V + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 2; i <= V; i++) {
        if (spf[i] == 0)
            for (int j = i; j <= V; j += i)
                if (spf[j] == 0) spf[j] = i;
    }

    int n; cin >> n;
    string out;
    out.reserve(1 << 20);

    while (n--) {
        int x; cin >> x;
        int tau = 1;
        while (x > 1) {
            int p = spf[x], e = 0;
            while (x % p == 0) { x /= p; e++; }
            tau *= (e + 1);
        }
        out += to_string(tau);
        out += '\n';
    }
    cout << out;
    return 0;
}