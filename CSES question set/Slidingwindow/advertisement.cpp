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
const ll NEG = LLONG_MIN/4;

int M;
vector<ll> A, B;                       // node line: A*x + B

void liInsert(int nd,int l,int r,ll a,ll b){
    int m=(l+r)>>1;
    if(a*(ll)m+b > A[nd]*(ll)m+B[nd]){ swap(a,A[nd]); swap(b,B[nd]); }
    if(l==r) return;
    if(a*(ll)l+b > A[nd]*(ll)l+B[nd]) liInsert(2*nd,l,m,a,b);
    else if(a*(ll)r+b > A[nd]*(ll)r+B[nd]) liInsert(2*nd+1,m+1,r,a,b);
}
void rInsert(int nd,int l,int r,int ql,int qr,ll a,ll b){
    if(qr<l||r<ql) return;
    if(ql<=l&&r<=qr){ liInsert(nd,l,r,a,b); return; }
    int m=(l+r)>>1;
    rInsert(2*nd,l,m,ql,qr,a,b);
    rInsert(2*nd+1,m+1,r,ql,qr,a,b);
}
ll qry(int nd,int l,int r,int x){
    ll res = A[nd]*(ll)x + B[nd];
    if(l==r) return res;
    int m=(l+r)>>1;
    if(x<=m) return max(res, qry(2*nd,l,m,x));
    return max(res, qry(2*nd+1,m+1,r,x));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> h(n+1);
    for(int i = 1; i <= n; i++) cin >> h[i];

    vector<int> L(n+1), R(n+1), st;      // nearest strictly-smaller bounds
    for(int i = 1; i <= n; i++){
        while(!st.empty() && h[st.back()] >= h[i]) st.pop_back();
        L[i] = (st.empty()? 0 : st.back()) + 1;
        st.pb(i);
    }
    st.clear();
    for(int i = n; i >= 1; i--){
        while(!st.empty() && h[st.back()] >= h[i]) st.pop_back();
        R[i] = (st.empty()? n+1 : st.back()) - 1;
        st.pb(i);
    }

    M = n - k + 1;
    A.assign(4*M+4, 0);
    B.assign(4*M+4, NEG);

    for(int i = 1; i <= n; i++){
        ll H = h[i]; int l = L[i], r = R[i];
        int t1 = min(l, r-k+1), t2 = max(l, r-k+1);
        int lo, hi;
        lo = max(1, l-k+1); hi = min(t1, M);                  // ramp up
        if(lo<=hi) rInsert(1,1,M,lo,hi, H, H*(ll)(k-l));
        lo = max(1, t1+1); hi = min(t2, M);                   // plateau
        if(lo<=hi) rInsert(1,1,M,lo,hi, 0, H*(ll)min(k, r-l+1));
        lo = max(1, t2+1); hi = min(r, M);                    // ramp down
        if(lo<=hi) rInsert(1,1,M,lo,hi, -H, H*(ll)(r+1));
    }

    string out;
    for(int x = 1; x <= M; x++){
        out += to_string(qry(1,1,M,x));
        out += ' ';
    }
    cout << out << "\n";
    return 0;
}