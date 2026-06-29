#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

typedef complex<double> cd;
const double PI = acos(-1.0);

void fft(vector<cd> &a, bool inv) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (inv ? -1 : 1);
        cd wl(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int k = 0; k < len / 2; k++) {
                cd u = a[i + k], v = a[i + k + len / 2] * w;
                a[i + k] = u + v;
                a[i + k + len / 2] = u - v;
                w *= wl;
            }
        }
    }
    if (inv) for (cd &x : a) x /= n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<ll> a(n), b(m);
    for (auto &v : a) cin >> v;
    for (auto &v : b) cin >> v;

    int need = n + m - 1;
    int sz = 1; while (sz < need) sz <<= 1;
    vector<cd> fa(sz, 0), fb(sz, 0);
    for (int i = 0; i < n; i++) fa[i] = (double)a[i];
    for (int i = 0; i < m; i++) fb[m - 1 - i] = (double)b[i];   // reversed mask

    fft(fa, false); fft(fb, false);
    for (int i = 0; i < sz; i++) fa[i] *= fb[i];
    fft(fa, true);

    string out;
    for (int s = 0; s < need; s++) {
        ll v = llround(fa[s].real());
        out += to_string(v);
        out += ' ';
    }
    out += '\n';
    cout << out;
}