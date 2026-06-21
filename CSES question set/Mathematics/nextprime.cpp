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
typedef unsigned long long ull;
typedef __int128 u128;

ull mulmod(ull a, ull b, ull m) { return (u128)a * b % m; }

ull power(ull a, ull b, ull m) {
    ull r = 1 % m;
    a %= m;
    while (b) {
        if (b & 1) r = mulmod(r, a, m);
        a = mulmod(a, a, m);
        b >>= 1;
    }
    return r;
}

bool isPrime(ull n) {
    if (n < 2) return false;
    for (ull p : {2ull,3ull,5ull,7ull,11ull,13ull,17ull,19ull,23ull,29ull,31ull,37ull})
        if (n % p == 0) return n == p;
    ull d = n - 1;
    int r = 0;
    while ((d & 1) == 0) { d >>= 1; r++; }
    for (ull a : {2ull,3ull,5ull,7ull,11ull,13ull,17ull,19ull,23ull,29ull,31ull,37ull}) {
        ull x = power(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool comp = true;
        for (int i = 0; i < r - 1; i++) {
            x = mulmod(x, x, n);
            if (x == n - 1) { comp = false; break; }
        }
        if (comp) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    string out;
    while (t--) {
        ull n; cin >> n;
        ull m = n + 1;
        while (!isPrime(m)) m++;
        out += to_string(m);
        out += '\n';
    }
    cout << out;
    return 0;
}