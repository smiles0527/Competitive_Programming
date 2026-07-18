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
mt19937 rng(0xC0FFEE);

struct Node { int val, pr, sz; bool rev; Node *l, *r, *par; };
int sz(Node* t) { return t ? t->sz : 0; }
void upd(Node* t) {
    if (t) { t->sz = sz(t->l) + sz(t->r) + 1;
        if (t->l) t->l->par = t; if (t->r) t->r->par = t; t->par = nullptr; }
}
void push(Node* t) {
    if (t && t->rev) { swap(t->l, t->r);
        if (t->l) t->l->rev ^= 1; if (t->r) t->r->rev ^= 1; t->rev = false; }
}
void merge(Node*& t, Node* a, Node* b) {
    if (!a) { t = b; return; } if (!b) { t = a; return; }
    push(a); push(b);
    if (a->pr > b->pr) { merge(a->r, a->r, b); t = a; }
    else { merge(b->l, a, b->l); t = b; }
    upd(t);
}
void split(Node* t, Node*& a, Node*& b, int k) {   // first k nodes -> a
    if (!t) { a = b = nullptr; return; }
    push(t);
    if (sz(t->l) + 1 <= k) { split(t->r, t->r, b, k - sz(t->l) - 1); a = t; }
    else { split(t->l, a, t->l, k); b = t; }
    upd(t);
}
int rankOf(Node* x) {                               // 0-indexed in-order position
    static vector<Node*> path;
    path.clear();
    for (Node* c = x; c; c = c->par) path.push_back(c);
    for (int i = (int)path.size() - 1; i >= 0; i--) push(path[i]);
    int r = sz(x->l);
    for (Node* c = x; c->par; c = c->par)
        if (c->par->r == c) r += sz(c->par->l) + 1;
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<Node*> byval(n + 1);
    Node* root = nullptr;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        Node* nd = new Node{x, (int)rng(), 1, false, nullptr, nullptr, nullptr};
        byval[x] = nd;
        merge(root, root, nd);
    }

    vector<pair<int,int>> ops;
    for (int v = 1; v <= n; v++) {
        int idx = rankOf(byval[v]);     // 0-indexed
        int target = v - 1;
        if (idx == target) continue;
        Node *A, *B, *C;
        split(root, A, B, target);
        split(B, B, C, idx - target + 1);
        if (B) B->rev ^= 1;
        merge(root, A, B);
        merge(root, root, C);
        ops.push_back({target + 1, idx + 1});   // 1-indexed output
    }

    string out = to_string(ops.size());
    out += '\n';
    for (auto& p : ops) { out += to_string(p.first); out += ' '; out += to_string(p.second); out += '\n'; }
    cout << out;
    return 0;
}