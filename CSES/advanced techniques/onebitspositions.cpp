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

    string str; cin >> str;
    int n = str.size();

    vector<cd> fa(1), fb(1);
    int need = 2 * n;                            // sum index range up to (n-1)+(n-1)
    int sz = 1; while (sz < need) sz <<= 1;
    fa.assign(sz, 0); fb.assign(sz, 0);
    for (int p = 0; p < n; p++) {
        double bit = (str[p] == '1') ? 1.0 : 0.0;
        fa[p] = bit;
        fb[n - 1 - p] = bit;                    // reversed copy
    }

    fft(fa, false); fft(fb, false);
    for (int i = 0; i < sz; i++) fa[i] *= fb[i];
    fft(fa, true);

    // pairs at distance k sit at convolution index (n-1)+k  (i>j, contribution counted once)
    string out;
    for (int k = 1; k <= n - 1; k++) {
        ll v = llround(fa[n - 1 + k].real());
        out += to_string(v);
        out += ' ';
    }
    out += '\n';
    cout << out;
}