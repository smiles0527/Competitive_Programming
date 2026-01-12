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

/*
===============================================================================
(1) INCORRECT idea: "Pairwise XOR <= K implies all three numbers share a common
    prefix of length something, so count triples by grouping on floor(x / 2^t)."
    Why it fails: the XOR constraint is pairwise and does not reduce to a single
    shared prefix unless K has a special form; it is sensitive to the highest
    differing bit and how K's bits interact.

    Attempted sketch (INCORRECT, do not use):
        choose t = msb(K)
        group by x >> t
        within each group: all pairs ok
        count C(sz,3) across groups
    Counterexample exists when K has lower bits set in a way that allows
    cross-group mixing for some, but not all, pairs.

(2) INCORRECT idea: "Build a graph on labels, connect if xor <= K, count 3-cliques
    by summing over adjacency intersections."
    Why it fails: labels go up to 1e18-ish in general problems; here labels can be
    huge and dense intervals; even with implicit representation, clique counting
    becomes intractable. Also adjacency is not sparse.

    INCORRECT code-like attempt (do not use):
        for each x:
            for each y in [x^0 .. x^K]:
                add edge x-y
        count triangles
    This is exponential in bits and not compressible as written.

(3) INCORRECT optimization: "For intervals, precompute for each bit position how
    many numbers have bit=1, then estimate pairs with xor<=K by DP over counts."
    Why it fails: xor<=K is not separable across bits by independent counts; it
    depends on lexicographic comparison of the xor bits to K.

(4) INCORRECT recursion: "Split by highest bit and always match 0-side with 0-side,
    1-side with 1-side, plus cross terms if K has that bit set."
    Why it fails: cross terms require adjusting a running offset that depends on
    counts of partner-side elements; missing that offset breaks the combinatorics.
    The final solution keeps a `cur` offset precisely for this reason.

===============================================================================
*/

#ifdef LOCAL
static string vec_intervals_to_string(const vector<pair<int,int>>& v) {
    stringstream ss;
    ss << "[";
    for (int i = 0; i < (int)v.size(); i++) {
        if (i) ss << ", ";
        ss << "(" << v[i].first << "," << v[i].second << ")";
    }
    ss << "]";
    return ss.str();
}
static void dbg_state(const char* tag,
                      const vector<pair<int,int>>& a,
                      const vector<pair<int,int>>& b,
                      int block,
                      int cur) {
    cerr << tag
         << " block=" << block
         << " cur=" << cur
         << " A=" << vec_intervals_to_string(a)
         << " B=" << vec_intervals_to_string(b)
         << "\n";
}
static void assert_intervals_in_range(const vector<pair<int,int>>& v, int lo, int hi) {
    for (auto &p : v) {
        if (!(lo <= p.first && p.first <= p.second && p.second <= hi)) {
            cerr << "Bad interval: (" << p.first << "," << p.second << ") expected in ["
                 << lo << "," << hi << "]\n";
            abort();
        }
    }
}
#endif

static void add_to_answer(const vector<pair<int,int>>& a,
                          const vector<pair<int,int>>& b,
                          int block,
                          Mint cur) {
#ifdef LOCAL
    dbg_state("enter add_to_answer", a, b, block, cur.v);
    if (block <= 0) { cerr << "block<=0\n"; abort(); }
    assert_intervals_in_range(a, 0, block - 1);
    assert_intervals_in_range(b, 0, block - 1);
#endif

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

    int half = block / 2;

#ifdef LOCAL
    if (block % 2 != 0) { cerr << "block not power-of-two?\n"; abort(); }
    if (half == 0) { cerr << "half==0 unexpected\n"; abort(); }
#endif

    vector<pair<int,int>> A0, A1, B0, B1;
    A0.reserve(a.size());
    A1.reserve(a.size());
    B0.reserve(b.size());
    B1.reserve(b.size());

    auto clip_push = [&](vector<pair<int,int>>& out, pair<int,int> p) {
        ckmax(p.first, 0);
        ckmin(p.second, half - 1);
        if (p.first <= p.second) out.push_back(p);
    };

    for (auto t : a) {
        clip_push(A0, t);
        clip_push(A1, {t.first - half, t.second - half});
    }
    for (auto t : b) {
        clip_push(B0, t);
        clip_push(B1, {t.first - half, t.second - half});
    }

    long long lenB0 = total_length(B0);
    long long lenB1 = total_length(B1);

#ifdef LOCAL
    assert_intervals_in_range(A0, 0, half - 1);
    assert_intervals_in_range(A1, 0, half - 1);
    assert_intervals_in_range(B0, 0, half - 1);
    assert_intervals_in_range(B1, 0, half - 1);
#endif

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

#ifdef LOCAL
    cerr << "deal: P=" << P << " half=" << half
         << " intervals=" << vec_intervals_to_string(v) << "\n";
#endif

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

#ifdef LOCAL
    assert_intervals_in_range(tot0, 0, half - 1);
    assert_intervals_in_range(tot1, 0, half - 1);
#endif

    long long len0 = total_length(tot0);
    long long len1 = total_length(tot1);

    ans += c3(len0);
    add_to_answer(tot0, tot1, half, 0);

    ans += c3(len1);
    add_to_answer(tot1, tot0, half, 0);
}

#ifdef LOCAL
static long long brute_count_general(const vector<pair<int,int>>& segs, int Kraw) {
    vector<int> xs;
    for (auto &p : segs) for (int x = p.first; x <= p.second; x++) xs.push_back(x);
    long long cnt = 0;
    for (int i = 0; i < (int)xs.size(); i++)
        for (int j = i + 1; j < (int)xs.size(); j++)
            for (int k = j + 1; k < (int)xs.size(); k++) {
                int a = xs[i], b = xs[j], c = xs[k];
                if ( ((a ^ b) <= Kraw) && ((a ^ c) <= Kraw) && ((b ^ c) <= Kraw) ) cnt++;
            }
    return cnt;
}
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    inv2 = mod_inv(2);
    inv6 = mod_inv(6);

    cin >> N >> K;
    int Kraw = K;
    K++;

    while (P <= K) P <<= 1;

    K = K - P / 2;

    Mint sing = Mint(P) * c2(K) + Mint(2) * c3(P / 2);

#ifdef LOCAL
    cerr << "N=" << N << " Kraw=" << Kraw << " internalK=" << K << " P=" << P << "\n";
    cerr << "sing=" << sing.v << "\n";
#endif

    map<int, vector<pair<int,int>>> todo;

    for (int i = 0; i < N; i++) {
        int L, R;
        cin >> L >> R;
        int LL = L / P, RR = R / P;

#ifdef LOCAL
        if (L > R) { cerr << "L>R\n"; abort(); }
#endif

        if (LL != RR) {
            if (RR - LL - 1 > 0) ans += Mint(RR - LL - 1) * sing;
            todo[LL].push_back({L % P, P - 1});
            todo[RR].push_back({0, R % P});
        } else {
            todo[LL].push_back({L % P, R % P});
        }
    }

#ifdef LOCAL
    cerr << "blocks touched=" << todo.size() << "\n";
#endif

    for (auto &kv : todo) {
#ifdef LOCAL
        cerr << "processing block id=" << kv.first << "\n";
#endif
        deal(kv.second);
    }

#ifdef LOCAL
    if ((int)todo.size() <= 2) {
        vector<pair<int,int>> segs;
        for (auto &kv : todo) {
            int base = kv.first * P;
            for (auto &p : kv.second) segs.push_back({base + p.first, base + p.second});
        }
        long long total = 0;
        long long elems = 0;
        for (auto &p : segs) elems += (long long)p.second - p.first + 1;
        if (elems <= 4000) {
            total = brute_count_general(segs, Kraw);
            cerr << "brute=" << total << " mod=" << (total % MOD) << " fast=" << ans.v << "\n";
        } else {
            cerr << "brute skipped elems=" << elems << "\n";
        }
    }
#endif

    cout << ans.v << "\n";
    return 0;
}
    