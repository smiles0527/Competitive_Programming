#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")

#define pb push_back
#define f first
#define s second

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;

const ll MOD = 1e9 + 7;
const int INF = 1e9;

struct Tr {
    int to[10];
    ll add[10];

    Tr(bool id = true) {
        for(int i = 0; i < 10; i++) {
            to[i] = i;
            add[i] = 0;
        }
    }
};

Tr all[20][10], one[10];

Tr merge_tr(const Tr& a, const Tr& b) {
    Tr c;
    for(int i = 0; i < 10; i++) {
        int mid = a.to[i];
        c.to[i] = b.to[mid];
        c.add[i] = a.add[i] + b.add[mid];
    }
    return c;
}

Tr build_one(int m) {
    Tr t;
    if(m == 0) return t;

    for(int r = 0; r < 10; r++) {
        if(r < m) {
            t.to[r] = r + 10 - m;
            t.add[r] = 1;
        } else {
            t.to[r] = 10 - m;
            t.add[r] = 2;
        }
    }
    return t;
}

Tr go(const string& s, int pos, int mx) {
    if(pos == (int)s.size()) return one[mx];

    int d = s[pos] - '0';
    int rem = (int)s.size() - pos - 1;

    Tr cur = go(s, pos + 1, max(mx, d));

    for(int x = d - 1; x >= 0; x--) {
        cur = merge_tr(cur, all[rem][max(mx, x)]);
    }

    return cur;
}

// ll maxd(ll v){ ll m=0; while(v){ m=max(m,v%10); v/=10; } return m; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for(int m = 0; m < 10; m++) one[m] = build_one(m);

    for(int mx = 0; mx < 10; mx++) all[0][mx] = one[mx];

    for(int len = 1; len < 20; len++) {
        for(int mx = 0; mx < 10; mx++) {
            Tr cur;
            for(int d = 9; d >= 0; d--) {
                cur = merge_tr(cur, all[len - 1][max(mx, d)]);
            }
            all[len][mx] = cur;
        }
    }

    ll n;
    cin >> n;

    // ll steps = 0;
    // while(n > 0){ ll g = maxd(n); n -= g; steps++; }
    // cout << steps << "\n";

    if(n == 0) {
        cout << 0 << '\n';
        return 0;
    }

    if(n < 10) {
        cout << 1 << '\n';
        return 0;
    }

    ll p = n / 10;
    int r = n % 10;

    string sp = to_string(p);
    Tr res = go(sp, 0, 0);

    ll ans = res.add[r] + (res.to[r] > 0);

    cout << ans << '\n';
    return 0;
}