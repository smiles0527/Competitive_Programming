#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,popcnt")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<unsigned> a(n);
    for (int i = 0; i < n; i++) {
        unsigned v = 0;
        for (int j = 0; j < k; j++) {          // pack bits MSB-first
            char ch; cin >> ch;
            v = (v << 1) | (ch - '0');
        }
        a[i] = v;
    }

    int best = INT_MAX;
    for (int i = 0; i < n; i++) {
        unsigned ai = a[i];
        for (int j = i + 1; j < n; j++) {
            int d = __builtin_popcount(ai ^ a[j]);
            if (d < best) best = d;
        }
        if (best == 0) break;                   // can't beat identical strings
    }

    cout << best << "\n";
}