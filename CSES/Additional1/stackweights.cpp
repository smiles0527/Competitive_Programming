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

int N;
vi mx, mn, lz;                          // suffix-sum array c[], global max/min

void app(int nd, ll v){ mx[nd]+=v; mn[nd]+=v; lz[nd]+=v; }
void push(int nd){
    if(lz[nd]){ app(2*nd, lz[nd]); app(2*nd+1, lz[nd]); lz[nd]=0; }
}
void upd(int nd, int l, int r, int ql, int qr, ll v){
    if(qr < l || r < ql) return;
    if(ql <= l && r <= qr){ app(nd, v); return; }
    push(nd);
    int md = (l+r)/2;
    upd(2*nd, l, md, ql, qr, v);
    upd(2*nd+1, md+1, r, ql, qr, v);
    mx[nd] = max(mx[2*nd], mx[2*nd+1]);
    mn[nd] = min(mn[2*nd], mn[2*nd+1]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    N = n;
    mx.assign(4*N, 0); mn.assign(4*N, 0); lz.assign(4*N, 0);

    string out; out.reserve(n*2);
    for(int t = 0; t < n; t++){
        int c, sk; cin >> c >> sk;
        ll dv = (sk == 1) ? 1 : -1;
        upd(1, 0, N-1, 0, c-1, dv);          // c_j changes for j ≤ c
        ll M = mx[1], m = mn[1];
        char res;
        if(M > 0 && m < 0) res = '?';
        else if(M > 0)     res = '>';
        else if(m < 0)     res = '<';
        else               res = '?';        // all zero ⇒ tie
        out.pb(res); out.pb('\n');
    }
    cout << out;
}