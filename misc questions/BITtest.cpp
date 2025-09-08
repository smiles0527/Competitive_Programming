#include <bits/stdc++.h>
using namespace std;

struct BIT {
    int n;
    vector<long long> t;
    BIT(int n=0): n(n), t(n+1,0) {}
    void init(int n_) { n=n_; t.assign(n+1,0); }
    void add(int i, long long v){ for(; i<=n; i+=i&-i) t[i]+=v; }
    long long sum(int i){ long long r=0; for(; i>0; i-=i&-i) r+=t[i]; return r; }
    long long range_sum(int l,int r){ if(r<l) return 0; return sum(r)-sum(l-1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    if(!(cin >> N >> M)) return 0;
    const int MAXV = 100000;
    vector<long long> a(N+1);
    for(int i=1;i<=N;i++) cin >> a[i];
    BIT bitIndex(N), bitFreq(MAXV+2);
    for(int i=1;i<=N;i++) bitIndex.add(i,a[i]);
    for(int i=1;i<=N;i++) bitFreq.add((int)a[i],1);
    for(int q=0;q<M;q++){
        char op; cin >> op;
        if(op=='C'){
            int i; long long v; cin >> i >> v;
            bitIndex.add(i, v - a[i]);
            bitFreq.add((int)a[i], -1);
            a[i]=v;
            int vv = (int)min<long long>(MAXV, max<long long>(1, v));
            bitFreq.add(vv, 1);
        }else if(op=='S'){
            int l,r; cin >> l >> r;
            if(l>r) swap(l,r);
            cout << bitIndex.range_sum(l,r) << "\n";
        }else if(op=='Q'){
            int v; cin >> v;
            if(v<=0) cout << 0 << "\n";
            else if(v>=MAXV) cout << bitFreq.sum(MAXV) << "\n";
            else cout << bitFreq.sum(v) << "\n";
        }
    }
    return 0;
}
