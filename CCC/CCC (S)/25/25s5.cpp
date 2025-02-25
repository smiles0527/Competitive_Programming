#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int RMAX = 1000003;
const ll NEG = -1e18;
 
struct Node {
    ll k, l;
};
 
inline Node combine(const Node &L, const Node &R) {
    return {L.k + R.k, max(L.l + R.k, R.l)};
}
 
struct SegTree {
    int size;
    vector<Node> tree;
    SegTree(int n) {
        size = 1;
        while(size < n) size *= 2;
        tree.assign(2*size, {0, NEG});
    }
    void build(vector<Node>& arr) {
        for (int i = 0; i < (int)arr.size(); i++) {
            tree[size + i] = arr[i];
        }
        for (int i = arr.size(); i < size; i++) {
            tree[size + i] = {0, NEG};
        }
        for (int i = size - 1; i > 0; i--) {
            tree[i] = combine(tree[2*i], tree[2*i+1]);
        }
    }
    void update(int pos, Node val) {
        pos += size - 1;
        tree[pos] = val;
        for(pos /= 2; pos; pos /= 2)
            tree[pos] = combine(tree[2*pos], tree[2*pos+1]);
    }
    Node query(int l, int r) {
        Node L = {0, NEG}, Rn = {0, NEG};
        l += size - 1; r += size - 1;
        while(l <= r) {
            if(l % 2 == 1) { L = combine(L, tree[l]); l++; }
            if(r % 2 == 0) { Rn = combine(tree[r], Rn); r--; }
            l /= 2; r /= 2;
        }
        return combine(L, Rn);
    }
};
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int Q; cin >> Q;
    vector<pair<int,int>> tasks; tasks.reserve(Q+1);
    tasks.push_back({0,0});
    vector<ll> A(RMAX+1,0);
    vector<int> cnt(RMAX+1,0);
    vector<Node> base(RMAX);
    for (int i = 1; i <= RMAX; i++){
        base[i-1] = {0, (ll)i};
    }
    SegTree seg(RMAX);
    seg.build(base);
    set<int> active;
    ll ans = 0;
    int addCount = 0;
    for (int qi = 0; qi < Q; qi++){
        char op; cin >> op;
        if(op=='A'){
            ll sp, tp; cin >> sp >> tp;
            int s = (int)((sp + ans) % RMAX);
            int t = (int)((tp + ans) % RMAX);
            if(s < 1) s = 1; if(t < 1) t = 1;
            addCount++;
            tasks.push_back({s,t});
            cnt[s]++;
            A[s] += t;
            seg.update(s, {A[s], (ll)s + A[s]});
            active.insert(s);
        } else {
            ll ip; cin >> ip;
            int idx = (int)((ip + ans) % RMAX);
            if(idx < 1) idx = 1;
            auto pr = tasks[idx];
            int s = pr.first, t = pr.second;
            tasks[idx] = {0,0};
            cnt[s]--;
            A[s] -= t;
            seg.update(s, {A[s], (ll)s + A[s]});
            if(cnt[s]==0) active.erase(s);
        }
        int mx = active.empty() ? 1 : *active.rbegin();
        Node res = seg.query(1, mx);
        ll T = max(1LL + res.k, res.l);
        ans = T - 1;
        cout << ans << "\n";
    }
    return 0;
}
