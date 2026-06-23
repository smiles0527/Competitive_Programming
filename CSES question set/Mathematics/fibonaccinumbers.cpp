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
typedef unsigned long long ull;

const ll MOD = 1e9 + 7;

pair<ll,ll> fib(ull n) {      // returns (F_n, F_{n+1})
    if (n == 0) return {0, 1};
    auto [a, b] = fib(n >> 1);          // a=F_k, b=F_{k+1}, k=n/2
    ll c = a * ((2 * b % MOD - a + MOD) % MOD) % MOD;   // F_{2k}
    ll d = (a * a % MOD + b * b % MOD) % MOD;           // F_{2k+1}
    if (n & 1) return {d, (c + d) % MOD};               // F_{2k+1}, F_{2k+2}
    else return {c, d};                                  // F_{2k},   F_{2k+1}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ull n; cin >> n;
    cout << fib(n).first << '\n';
    return 0;
}