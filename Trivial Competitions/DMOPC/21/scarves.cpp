#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    int pr;
    int sz;
    Node *l, *r, *p;
    Node(int v, int pr_) : val(v), pr(pr_), sz(1), l(nullptr), r(nullptr), p(nullptr) {}
};

int getsz(Node* t) { return t ? t->sz : 0; }

void pull(Node* t) {
    if (!t) return;
    t->sz = 1 + getsz(t->l) + getsz(t->r);
    if (t->l) t->l->p = t;
    if (t->r) t->r->p = t;
}

Node* merge_t(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->pr < b->pr) {
        a->r = merge_t(a->r, b);
        if (a->r) a->r->p = a;
        pull(a);
        a->p = nullptr;
        return a;
    } else {
        b->l = merge_t(a, b->l);
        if (b->l) b->l->p = b;
        pull(b);
        b->p = nullptr;
        return b;
    }
}

pair<Node*, Node*> split_t(Node* t, int k) {
    if (!t) return {nullptr, nullptr};
    int ls = getsz(t->l);
    if (k <= ls) {
        auto pr = split_t(t->l, k);
        t->l = pr.second;
        if (t->l) t->l->p = t;
        pull(t);
        if (pr.first) pr.first->p = nullptr;
        t->p = nullptr;
        return {pr.first, t};
    } else {
        auto pr = split_t(t->r, k - ls - 1);
        t->r = pr.first;
        if (t->r) t->r->p = t;
        pull(t);
        if (pr.second) pr.second->p = nullptr;
        t->p = nullptr;
        return {t, pr.second};
    }
}

int pos_of(Node* x) {
    int res = getsz(x->l) + 1;
    while (x->p) {
        if (x == x->p->r) res += getsz(x->p->l) + 1;
        x = x->p;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    mt19937 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());

    vector<Node*> node(N + 1, nullptr);
    Node* root = nullptr;

    for (int i = 1; i <= N; i++) {
        node[i] = new Node(i, (int)uniform_int_distribution<int>(1, INT_MAX)(rng));
        root = merge_t(root, node[i]);
    }

    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        int pa = pos_of(node[a]);
        int pb = pos_of(node[b]);

        auto s1 = split_t(root, pb);
        auto s2 = split_t(s1.first, pa - 1);
        Node* left = s2.first;
        Node* mid = s2.second;
        Node* right = s1.second;

        root = merge_t(left, right);

        if (c == 0) {
            root = merge_t(mid, root);
        } else {
            int pc = pos_of(node[c]);
            auto s3 = split_t(root, pc);
            root = merge_t(merge_t(s3.first, mid), s3.second);
        }
    }

    vector<int> out;
    out.reserve(N);
    vector<Node*> st;
    Node* cur = root;
    while (cur || !st.empty()) {
        while (cur) {
            st.push_back(cur);
            cur = cur->l;
        }
        cur = st.back();
        st.pop_back();
        out.push_back(cur->val);
        cur = cur->r;
    }

    for (int i = 0; i < N; i++) {
        if (i) cout << ' ';
        cout << out[i];
    }
    cout << "\n";
    return 0;
}
