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

int n, q;
vector<ll> bit;

void upd(int i, ll v){
    for (; i <= n; i += i & -i) bit[i] += v;
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

    vector<int> x(n + 1);
    for (int i = 1; i <= n; i++) cin >> x[i];

    vector<int> A(q), B(q), ord(q);
    for (int i = 0; i < q; i++){ cin >> A[i] >> B[i]; ord[i] = i; }
    sort(ord.begin(), ord.end(), [&](int u, int v){ return B[u] < B[v]; });

    bit.assign(n + 1, 0);
    unordered_map<int,int> last;        // value -> last marked position
    last.reserve(2*n);

    vector<ll> ans(q);
    int j = 1;                          // sweep pointer
    for (int t : ord){
        int a = A[t], b = B[t];
        while (j <= b){
            auto it = last.find(x[j]);
            if (it != last.end()) upd(it->second, -1);  // unmark old occurrence
            upd(j, 1);
            last[x[j]] = j;
            j++;
        }
        ans[t] = pre(b) - pre(a - 1);
    }

    for (int i = 0; i < q; i++) cout << ans[i] << '\n';
    return 0;
}