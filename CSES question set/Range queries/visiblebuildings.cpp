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

int n, q, M;                            // M = L-domain size (n+1)
vector<ll> bit;

void upd(int i, ll v){
    for (; i <= M; i += i & -i) bit[i] += v;
}
ll pre(int i){
    ll r = 0;
    for (; i > 0; i -= i & -i) r += bit[i];
    return r;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    vector<ll> h(n + 1);
    for (int i = 1; i <= n; i++) cin >> h[i];

    vector<int> L(n + 1);               // nearest left idx with h >= h[j], else 0
    vector<int> st;                     // monotonic stack of indices
    for (int j = 1; j <= n; j++){
        while (!st.empty() && h[st.back()] < h[j]) st.pop_back();
        L[j] = st.empty() ? 0 : st.back();
        st.pb(j);
    }

    vector<int> A(q), B(q);
    vector<int> ord(q);
    for (int i = 0; i < q; i++){ cin >> A[i] >> B[i]; ord[i] = i; }
    sort(ord.begin(), ord.end(), [&](int x, int y){ return B[x] < B[y]; });

    M = n + 1;
    bit.assign(M + 1, 0);

    vector<ll> ans(q);
    int j = 1;                          // sweep pointer over positions
    for (int t : ord){
        int b = B[t], a = A[t];
        while (j <= b){ upd(L[j] + 1, 1); j++; }   // index L by +1 (L can be 0)
        ll Fba = pre(a);                            // count L_j <= a-1  ==  index <= a
        ans[t] = Fba - (a - 1);
    }

    for (int i = 0; i < q; i++) cout << ans[i] << '\n';
    return 0;
}