#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
struct Node { int maxVal, maxIdx, minActive, maxActive; };
int N, Q; 
vector<int> freq;
vector<Node> seg;
Node mergeN(const Node &L, const Node &R) {
    Node res;
    if(L.maxVal >= R.maxVal) { res.maxVal = L.maxVal; res.maxIdx = L.maxIdx; }
    else { res.maxVal = R.maxVal; res.maxIdx = R.maxIdx; }
    res.minActive = min(L.minActive, R.minActive);
    res.maxActive = max(L.maxActive, R.maxActive);
    return res;
}
void build(int idx, int l, int r) {
    if(l == r) {
        seg[idx].maxVal = freq[l];
        seg[idx].maxIdx = l;
        seg[idx].minActive = (freq[l] > 0 ? l : INF);
        seg[idx].maxActive = (freq[l] > 0 ? l : -1);
        return;
    }
    int m = (l + r) / 2;
    build(idx*2, l, m); build(idx*2+1, m+1, r);
    seg[idx] = mergeN(seg[idx*2], seg[idx*2+1]);
}
void upd(int idx, int l, int r, int pos, int val) {
    if(l == r) {
        freq[pos] = val;
        seg[idx].maxVal = val;
        seg[idx].maxIdx = pos;
        seg[idx].minActive = (val > 0 ? pos : INF);
        seg[idx].maxActive = (val > 0 ? pos : -1);
        return;
    }
    int m = (l + r) / 2;
    if(pos <= m) upd(idx*2, l, m, pos, val);
    else         upd(idx*2+1, m+1, r, pos, val);
    seg[idx] = mergeN(seg[idx*2], seg[idx*2+1]);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> Q;
    freq.resize(N+1, 0);
    vector<int> cow(N+1);
    for(int i = 1; i <= N; i++){
        cin >> cow[i];
        freq[cow[i]]++;
    }
    seg.resize(4*(N+1));
    build(1, 1, N);
    while(Q--){
        int i, x; 
        cin >> i >> x;
        int old = cow[i];
        cow[i] = x;
        upd(1, 1, N, old, freq[old]-1);
        upd(1, 1, N, x, freq[x]+1);
        int Fmax = seg[1].maxVal, p = seg[1].maxIdx;
        int L = seg[1].minActive, R = seg[1].maxActive;
        int ans = 0;
        if(L < R) {
            int c1 = max(p - L, R - p);
            int c2 = (freq[L] + freq[R] >= Fmax ? R - L : 0);
            ans = max(c1, c2);
        }
        cout << ans << "\n";
    }
    return 0;
}
