// ============================================================================
// COMPETITIVE PROGRAMMING TEMPLATE
// ============================================================================
// Fast I/O, common utilities, and debugging macros for CP

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// TYPE ALIASES
// ============================================================================
using ll = long long;
using ld = long double;
using db = double;
using str = string;

using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;

using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using vs = vector<str>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;

// ============================================================================
// CONSTANTS
// ============================================================================
const int MOD = 1e9 + 7;
const ll INF = 1e18;
const int MX = 2e5 + 5;
const ld PI = acos(-1.0);

// Direction vectors (4-directional)
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

// Direction vectors (8-directional)
const int dx8[8] = {1, 1, 0, -1, -1, -1, 0, 1};
const int dy8[8] = {0, 1, 1, 1, 0, -1, -1, -1};

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

// Check min/max with update
template <typename T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, true : false; }

template <typename T>
bool ckmax(T &a, const T &b) { return a < b ? a = b, true : false; }

// Power
ll power(ll a, ll b, ll mod = MOD) {
    ll res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// Modular inverse
ll modinv(ll a, ll mod = MOD) { return power(a, mod - 2, mod); }

// GCD
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

// LCM
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

// Binary search on answer (left)
template <typename T, typename F>
T bsearch_left(T lo, T hi, F check) {
    while (lo < hi) {
        T mid = lo + (hi - lo) / 2;
        if (check(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

// Binary search on answer (right)
template <typename T, typename F>
T bsearch_right(T lo, T hi, F check) {
    while (lo < hi) {
        T mid = lo + (hi - lo + 1) / 2;
        if (check(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    return lo;
}

// ============================================================================
// MACROS
// ============================================================================

#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

#define pb push_back
#define eb emplace_back
#define fi first
#define se second

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define ROF(i, a, b) for (int i = (b) - 1; i >= (a); i--)
#define REP(i, n) FOR(i, 0, n)
#define RREP(i, n) ROF(i, 0, n)

#define SORT(x) sort(all(x))
#define RSORT(x) sort(rall(x))

// ============================================================================
// I/O OPTIMIZATION
// ============================================================================

void setup() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);
}

// ============================================================================
// DEBUG (LOCAL ONLY)
// ============================================================================

#ifdef LOCAL
#define DEBUG 1
#else
#define DEBUG 0
#endif

#define dbg(...)                                 \
    do {                                         \
        if (DEBUG) {                             \
            cerr << "[" << __LINE__ << "] ";     \
            _dbg(#__VA_ARGS__, __VA_ARGS__);     \
            cerr << "\n";                        \
        }                                        \
    } while (0)

template <typename T>
void _dbg(const char *name, T val) {
    cerr << name << " = " << val;
}

template <typename T, typename... Args>
void _dbg(const char *names, T val, Args... args) {
    const char *comma = strchr(names, ',');
    cerr.write(names, comma - names) << " = " << val << ", ";
    _dbg(comma + 1, args...);
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    setup();

    // Start solution here
    
    return 0;
}
