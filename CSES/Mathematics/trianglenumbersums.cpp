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
bool isSquare(ll x) {
    if (x < 0) return false;
    ll r = (ll)sqrtl((long double)x);
    while (r * r > x) r--;
    while ((r+1)*(r+1) <= x) r++;
    return r * r == x;
}

vector<int> primes;
void sieve(int LIM) {
    vector<bool> comp(LIM + 1, false);
    for (int i = 2; i <= LIM; i++) {
        if (!comp[i]) {
            primes.push_back(i);
            for (ll j = (ll)i*i; j <= LIM; j += i) comp[j] = true;
        }
    }
}

// is N a sum of two squares? every prime p≡3 (mod 4) appears to even power
bool sumTwoSquares(ll N) {
    for (int p : primes) {
        if ((ll)p * p > N) break;
        if (N % p == 0) {
            int e = 0;
            while (N % p == 0) { N /= p; e++; }
            if (p % 4 == 3 && (e & 1)) return false;
        }
    }
    // leftover prime N (if >1)
    if (N > 1 && N % 4 == 3) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve(3000000);

    int t; cin >> t;
    string out;
    while (t--) {
        ll n; cin >> n;
        if (isSquare(8*n + 1)) out += '1';
        else if (sumTwoSquares(8*n + 2)) out += '2';
        else out += '3';
        out += '\n';
    }
    cout << out;
    return 0;
}