#include <bits/stdc++.h>
using namespace std;
struct DPState {
    int len;
    unsigned long long h1, h2;
};
 

const unsigned long long BASE = 131ULL; 
const unsigned long long MOD1 = 1000000007ULL;
const unsigned long long MOD2 = 1000000009ULL;
 

DPState mergeElem(int x, const DPState &state) {
    DPState res;
    res.len = state.len + 1;
    res.h1 = (x + (BASE * state.h1) % MOD1) % MOD1;
    res.h2 = (x + (BASE * state.h2) % MOD2) % MOD2;
    return res;
}
 



bool dpStateGreater(const DPState &A, const DPState &B) {
    if(A.len != B.len)
        return A.len > B.len; 
    if(A.h1 != B.h1)
        return A.h1 > B.h1;
    return A.h2 > B.h2;
}
 

struct SegTree {
    int n;
    vector<DPState> tree;
    SegTree(int n) : n(n) { tree.resize(4*n); }
    
    
    DPState combine(const DPState &a, const DPState &b) {
        return dpStateGreater(a, b) ? a : b;
    }
    void build(vector<DPState> &arr, int idx, int l, int r) {
        if(l == r) {
            tree[idx] = arr[l];
            return;
        }
        int mid = (l+r)/2;
        build(arr, idx*2, l, mid);
        build(arr, idx*2+1, mid+1, r);
        tree[idx] = combine(tree[idx*2], tree[idx*2+1]);
    }
    DPState query(int idx, int l, int r, int ql, int qr) {
        if(ql>r || qr<l) return {0, 0, 0};
        if(ql<=l && r<=qr) return tree[idx];
        int mid = (l+r)/2;
        DPState left = query(idx*2, l, mid, ql, qr);
        DPState right = query(idx*2+1, mid+1, r, ql, qr);
        return combine(left, right);
    }
};

 

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T; cin >> T;
    while(T--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i=0; i<n; i++) cin >> a[i];
        
        
        
        vector<DPState> dp0(n+1), dp1(n+1);
        dp0[n] = {0, 0, 0};
        dp1[n] = {0, 0, 0};
        
        
        vector<unsigned long long> pow1(n+1), pow2(n+1);
        pow1[0] = pow2[0] = 1;
        for (int i=1; i<=n; i++){
            pow1[i] = (pow1[i-1] * BASE) % MOD1;
            pow2[i] = (pow2[i-1] * BASE) % MOD2;
        }
        
        
        for (int i = n-1; i >= 0; i--){
            
            DPState take = mergeElem(a[i], dp0[i+1]); 
            DPState skip = dp0[i+1];
            dp0[i] = dpStateGreater(take, skip) ? take : skip;
            
            DPState take1 = mergeElem(a[i], dp1[i+1]);
            DPState skip1 = dp1[i+1];
            dp1[i] = dpStateGreater(take1, skip1) ? take1 : skip1;
            
            
            
            
            
            
        }
        
        
        
        cout << dp0[0].len << "\n";
        
    }
    return 0;
}
