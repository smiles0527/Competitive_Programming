#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9 + 7, X = 1e6 + 5;

ll p[X], d[X], w[X], iw[X];
int o[X], c[X], r[X];
vector<int> q[X];
//m
ll mp(ll b, ll e) {
    ll r = 1; b %= M;
    while (e) {
        if (e & 1) r = r * b % M;
        b = b * b % M; e >>= 1;
    }
    return r;
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; ll k;
    if (!(cin >> n >> k)) return 0;
    for (int i = 1; i <= n; i++) cin >> p[i] >> o[i];

    w[0] = iw[0] = 1;
    ll i2 = mp(2, M - 2);
    for (int i = 1; i <= n; i++) {
        w[i] = w[i - 1] * 2 % M;
        iw[i] = iw[i - 1] * i2 % M;//inverse
        c[i] = c[i - 1] + !o[i];
    }

    for (int i = 1; i <= n; i++) 
        if (o[i]) r[i] = upper_bound(p + 1, p + n + 1, p[i] + k) - p - 1;

    ll s1 = 0, s2 = 0;
    for (int i = 1; i <= n; i++) {
        for (int x : q[i]) {
            s1 = (s1 - d[x] * iw[c[x]] % M + M) % M;
            s2 = (s2 + d[x] * w[c[r[x]] - c[x]]) % M; //add d[x] * 2^(#non-o between x and r[x])
        }
        if (o[i]) {
            d[i] = (1 + s1 * w[c[i - 1]] + s2) % M; 
            s1 = (s1 + d[i] * iw[c[i]]) % M;
            if (r[i] + 2 <= n) q[r[i] + 2].push_back(i);
        }
    }

    ll a = 0;
    for (int i = 1; i <= n; i++) 
        if (o[i]) a = (a + d[i] * w[c[r[i]] - c[i]]) % M;

    cout << a << endl;
}