#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000007;

struct Mint {
    int v;
    Mint(long long x = 0) {
        x %= MOD;
        if (x < 0) x += MOD;
        v = (int)x;
    }
    explicit operator int() const { return v; }
    Mint& operator+=(const Mint& o) { v += o.v; if (v >= MOD) v -= MOD; return *this; }
    Mint& operator-=(const Mint& o) { v -= o.v; if (v < 0) v += MOD; return *this; }
    Mint& operator*=(const Mint& o) { v = (int)((long long)v * o.v % MOD); return *this; }
    friend Mint operator+(Mint a, const Mint& b) { return a += b; }
    friend Mint operator-(Mint a, const Mint& b) { return a -= b; }
    friend Mint operator*(Mint a, const Mint& b) { return a *= b; }
};

static Mint mod_pow(Mint a, long long e) {
    Mint r = 1;
    while (e > 0) {
        if (e & 1) r *= a;
        a *= a;
        e >>= 1;
    }
    return r;
}
static Mint mod_inv(Mint a) { return mod_pow(a, MOD - 2); }

static inline bool ckmin(int& a, int b) { if (b < a) { a = b; return true; } return false; }
static inline bool ckmax(int& a, int b) { if (a < b) { a = b; return true; } return false; }

static int N;
static int K;
static int P = 1;
static Mint ans;

static Mint inv2, inv6;

static inline Mint c2(long long x) {
    if (x < 2) return 0;
    return Mint(x) * Mint(x - 1) * inv2;
}
static inline Mint c3(long long x) {
    if (x < 3) return 0;
    return Mint(x) * Mint(x - 1) * Mint(x - 2) * inv6;
}

static long long total_length(const vector<pair<int,int>>& v) {
    long long s = 0;
    for (auto &t : v) s += (long long)t.second - t.first + 1;
    return s;
}

static void add_to_answer(const vector<pair<int,int>>& a,
                          const vector<pair<int,int>>& b,
                          int block,
                          Mint cur) {
    if (a.empty()) return;
    if (b.empty()) {
        ans += Mint(total_length(a)) * c2((int)cur.v);
        return;
    }
    if ((int)b.size() == 1 && b[0].first == 0 && b[0].second == block - 1) {
        cur += (Mint)((block - 1) & K);
        ans += Mint(total_length(a)) * c2((int)cur.v);
        return;
    }

    vector<pair<int,int>> A0, A1, B0, B1;
    A0.reserve(a.size());
    A1.reserve(a.size());
    B0.reserve(b.size());
    B1.reserve(b.size());

    auto ad0 = [&](vector<pair<int,int>>& v, pair<int,int> p, int half) {
        ckmax(p.first, 0);
        ckmin(p.second, half - 1);
        if (p.first <= p.second) v.push_back(p);
    };
    int half = block / 2;

    for (auto t : a) {
        ad0(A0, t, half);
        ad0(A1, {t.first - half, t.second - half}, half);
    }
    for (auto t : b) {
        ad0(B0, t, half);
        ad0(B1, {t.first - half, t.second - half}, half);
    }

    long long lenB0 = total_length(B0);
    long long lenB1 = total_length(B1);

    if (K & half) {
        add_to_answer(A0, B1, half, cur + Mint(lenB0));
        add_to_answer(A1, B0, half, cur + Mint(lenB1));
    } else {
        add_to_answer(A0, B0, half, cur);
        add_to_answer(A1, B1, half, cur);
    }
}

static void deal(const vector<pair<int,int>>& v) {
    int half = P / 2;
    vector<pair<int,int>> tot0, tot1;
    tot0.reserve(v.size());
    tot1.reserve(v.size());

    for (auto t : v) {
        int a = t.first / half;
        int b = t.second / half;
        if (a < b) {
            tot0.push_back({t.first, half - 1});
            tot1.push_back({0, t.second - half});
        } else {
            if (a == 0) tot0.push_back({t.first % half, t.second % half});
            else tot1.push_back({t.first % half, t.second % half});
        }
    }

    long long len0 = total_length(tot0);
    long long len1 = total_length(tot1);

    ans += c3(len0);
    add_to_answer(tot0, tot1, half, 0);

    ans += c3(len1);
    add_to_answer(tot1, tot0, half, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    inv2 = mod_inv(2);
    inv6 = mod_inv(6);

    cin >> N >> K;
    K++;

    while (P <= K) P <<= 1;

    K = K - P / 2;

    Mint sing = Mint(P) * c2(K) + Mint(2) * c3(P / 2);

    map<int, vector<pair<int,int>>> todo;

    for (int i = 0; i < N; i++) {
        int L, R;
        cin >> L >> R;
        int LL = L / P, RR = R / P;
        if (LL != RR) {
            if (RR - LL - 1 > 0) ans += Mint(RR - LL - 1) * sing;
            todo[LL].push_back({L % P, P - 1});
            todo[RR].push_back({0, R % P});
        } else {
            todo[LL].push_back({L % P, R % P});
        }
    }

    for (auto &kv : todo) deal(kv.second);

    cout << ans.v << "\n";
    return 0;
}
