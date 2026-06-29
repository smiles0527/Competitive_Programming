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
typedef __int128 lll;
const ll MOD = 1e9 + 7;

// upper hull of points (k, S[k]), k=1..n ; returns the indices
vector<int> hull(const vector<ll>& S, int n){
    vector<int> h;
    for(int k = 1; k <= n; k++){
        while(h.size() >= 2){
            int o = h[h.size()-2], a = h[h.size()-1];
            lll lhs = (lll)(a-o)*(S[k]-S[o]);     // cross(O,A,K) >= 0 => A below => pop
            lll rhs = (lll)(S[a]-S[o])*(k-o);
            if(lhs - rhs >= 0) h.pop_back(); else break;
        }
        h.pb(k);
    }
    return h;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<ll> A(n+1, 0), B(n+1, 0);
    for(int i = 1; i <= n; i++){ ll x; cin >> x; A[i] = A[i-1] + x; }
    for(int i = 1; i <= n; i++){ ll x; cin >> x; B[i] = B[i-1] + x; }

    vector<int> ha = hull(A, n), hb = hull(B, n);
    int La = ha.size(), Lb = hb.size();

    int ia = 0, ib = 0;
    int bi = ha[0], bj = hb[0];
    lll bP = (lll)A[bi] + B[bj], bD = (lll)bi + bj;     // best avg = bP/bD

    auto better = [&](int i, int j){
        lll P = (lll)A[i] + B[j], D = (lll)i + j;
        if(P*bD > bP*D){ bP = P; bD = D; bi = i; bj = j; }   // exact compare
    };

    while(ia < La-1 || ib < Lb-1){
        bool adA;
        if(ia == La-1) adA = false;
        else if(ib == Lb-1) adA = true;
        else{                                    // advance the steeper next edge
            ll nA = A[ha[ia+1]]-A[ha[ia]], dA = ha[ia+1]-ha[ia];
            ll nB = B[hb[ib+1]]-B[hb[ib]], dB = hb[ib+1]-hb[ib];
            adA = ( (lll)nA*dB >= (lll)nB*dA );
        }
        if(adA) ia++; else ib++;
        better(ha[ia], hb[ib]);                  // visit this Minkowski vertex
    }

    cout << bi << " " << bj << "\n";
}