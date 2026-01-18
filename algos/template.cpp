#include <bits/stdc++.h>
#include <array>
using namespace std;
 
using ll = long long;
using ld = long double;
using db = double; 
using str = string; 
 
using pi = pair<int,int>;
using pl = pair<ll,ll>;
using pd = pair<db,db>;
 
using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;
using vd = vector<db>; 
using vs = vector<str>;
using vpi = vector<pi>;
using vpl = vector<pl>; 
using vpd = vector<pd>;
 
#define tcT template<class T
#define tcTU tcT, class U

tcT> using V = vector<T>; 
tcT, size_t SZ> using AR = array<T,SZ>; 
tcT> using PR = pair<T,T>;
 

#define mp make_pair
#define f first
#define s second
 


#define sz(x) int((x).size())
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define rall(x) x.rbegin(), x.rend() 
#define sor(x) sort(all(x)) 
#define rsz resize
#define ins insert 
#define ft front()
#define bk back()
#define pb push_back
#define eb emplace_back 
#define pf push_front
 
#define lb lower_bound
#define ub upper_bound 
tcT> int lwb(V<T>& a, const T& b) { return int(lb(all(a),b)-bg(a)); }
 

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) for FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define trav(a,x) for (auto& a: x)
 
const int MOD = 1e9+7; 
const int MX = 2e5+5;
const ll INF = 1e18; 
const ld PI = acos((ld)-1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
template<class T> using pqg = priority_queue<T,vector<T>,greater<T>>;
 


constexpr int pct(int x) { return __builtin_popcount(x); } 
constexpr int bits(int x) { 
	return x == 0 ? 0 : 31-__builtin_clz(x); } 
constexpr int p2(int x) { return 1<<x; }
constexpr int msk2(int x) { return p2(x)-1; }
 
ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } 
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } 
 
tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } 
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; }
 
tcTU> T fstTrue(T lo, T hi, U f) {
	hi ++; assert(lo <= hi); 
	while (lo < hi) { 
		T mid = lo+(hi-lo)/2;
		f(mid) ? hi = mid : lo = mid+1; 
	} 
	return lo;
}
tcTU> T lstTrue(T lo, T hi, U f) {
	lo --; assert(lo <= hi); 
	while (lo < hi) { 
		T mid = lo+(hi-lo+1)/2;
		f(mid) ? lo = mid : hi = mid-1;
	} 
	return lo;
}
tcT> void remDup(vector<T>& v) { 
	sort(all(v)); v.erase(unique(all(v)),end(v)); }
tcTU> void erase(T& t, const U& u) { 
	auto it = t.find(u); assert(it != end(t));
	t.erase(it); } 
 

#define tcTUU tcT, class ...U
tcT> void re(complex<T>& c);
tcTU> void re(pair<T,U>& p);
tcT> void re(V<T>& v);
tcT, size_t SZ> void re(AR<T,SZ>& a);
 
tcT> void re(T& x) { cin >> x; }
void re(db& d) { str t; re(t); d = stod(t); }
void re(ld& d) { str t; re(t); d = stold(t); }
tcTUU> void re(T& t, U&... u) { re(t); re(u...); }
 
tcT> void re(complex<T>& c) { T a,b; re(a,b); c = {a,b}; }
tcTU> void re(pair<T,U>& p) { re(p.f,p.s); }
tcT> void re(V<T>& x) { trav(a,x) re(a); }
tcT, size_t SZ> void re(AR<T,SZ>& x) { trav(a,x) re(a); }
tcT> void rv(int n, V<T>& x) { x.rsz(n); re(x); }
 

#define ts to_string
str ts(char c) { return str(1,c); }
str ts(const char* s) { return (str)s; }
str ts(str s) { return s; }
str ts(bool b) { 
	#ifdef LOCAL
		return b ? "true" : "false"; 
	#else 
		return ts((int)b);
	#endif
}
tcT> str ts(complex<T> c) { 
	stringstream ss; ss << c; return ss.str(); }
str ts(V<bool> v) {
	str res = "{"; F0R(i,sz(v)) res += char('0'+v[i]);
	res += "}"; return res; }
template<size_t SZ> str ts(bitset<SZ> b) {
	str res = ""; F0R(i,SZ) res += char('0'+b[i]);
	return res; }
tcTU> str ts(pair<T,U> p);
tcT> str ts(T v) { 
	#ifdef LOCAL
		bool fst = 1; str res = "{";
		for (const auto& x: v) {
			if (!fst) res += ", ";
			fst = 0; res += ts(x);
		}
		res += "}"; return res;
	#else
		bool fst = 1; str res = "";
		for (const auto& x: v) {
			if (!fst) res += " ";
			fst = 0; res += ts(x);
		}
		return res;
 
	#endif
}
tcTU> str ts(pair<T,U> p) {
	#ifdef LOCAL
		return "("+ts(p.f)+", "+ts(p.s)+")"; 
	#else
		return ts(p.f)+" "+ts(p.s);
	#endif
}
 

tcT> void pr(T x) { cout << ts(x); }
tcTUU> void pr(const T& t, const U&... u) { 
	pr(t); pr(u...); }
void ps() { pr("\n"); } 
tcTUU> void ps(const T& t, const U&... u) { 
	pr(t); if (sizeof...(u)) pr(" "); ps(u...); }
 

void DBG() { cerr << "]" << endl; }
tcTUU> void DBG(const T& t, const U&... u) {
	cerr << ts(t); if (sizeof...(u)) cerr << ", ";
	DBG(u...); }
#ifdef LOCAL 
	#define dbg(...) cerr << "Line(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
	#define chk(...) if (!(__VA_ARGS__)) cerr << "Line(" << __LINE__ << ") -> function(" \
		 << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\n", exit(0);
#else
	#define dbg(...) 0
	#define chk(...) 0
#endif
 
void setPrec() { cout << fixed << setprecision(15); }
void unsyncIO() { cin.tie(0)->sync_with_stdio(0); }

void setIn(str s) { freopen(s.c_str(),"r",stdin); }
void setOut(str s) { freopen(s.c_str(),"w",stdout); }
void setIO(str s = "") {
	unsyncIO(); setPrec();
	
	
	
	if (sz(s)) setIn(s+".in"), setOut(s+".out"); 
}
 
/**
 * Description: modular arithmetic operations 
 * Source: 
	* KACTL
	* https:
	* https:
	* https:
	* also see https:
 * Verification: 
	* https:
 */
 
template<int MOD, int RT> struct mint {
	static const int mod = MOD;
	static constexpr mint rt() { return RT; } 
	int v; explicit operator int() const { return v; } 
	mint() { v = 0; }
	mint(ll _v) { v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
		if (v < 0) v += MOD; }
	friend bool operator==(const mint& a, const mint& b) { 
		return a.v == b.v; }
	friend bool operator!=(const mint& a, const mint& b) { 
		return !(a == b); }
	friend bool operator<(const mint& a, const mint& b) { 
		return a.v < b.v; }
	friend void re(mint& a) { ll x; re(x); a = mint(x); }
	friend str ts(mint a) { return ts(a.v); }
   
	mint& operator+=(const mint& m) { 
		if ((v += m.v) >= MOD) v -= MOD; 
		return *this; }
	mint& operator-=(const mint& m) { 
		if ((v -= m.v) < 0) v += MOD; 
		return *this; }
	mint& operator*=(const mint& m) { 
		v = (ll)v*m.v%MOD; return *this; }
	mint& operator/=(const mint& m) { return (*this) *= inv(m); }
	friend mint pow(mint a, ll p) {
		mint ans = 1; assert(p >= 0);
		for (; p; p /= 2, a *= a) if (p&1) ans *= a;
		return ans; }
	friend mint inv(const mint& a) { assert(a.v != 0); 
		return pow(a,MOD-2); }
		
	mint operator-() const { return mint(-v); }
	mint& operator++() { return *this += 1; }
	mint& operator--() { return *this -= 1; }
	friend mint operator+(mint a, const mint& b) { return a += b; }
	friend mint operator-(mint a, const mint& b) { return a -= b; }
	friend mint operator*(mint a, const mint& b) { return a *= b; }
	friend mint operator/(mint a, const mint& b) { return a /= b; }
};
 
typedef mint<MOD,5> mi; 
typedef vector<mi> vmi;
typedef pair<mi,mi> pmi;
typedef vector<pmi> vpmi;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    #ifdef DEBUG

    auto debug_separator = []() { cerr << "====================\n"; };
    auto debug_line = []() { cerr << "--------------------\n"; };
    auto debug_newline = []() { cerr << "\n"; };
    auto debug_header = [](const string& s) { cerr << "=== " << s << " ===\n"; };
    auto debug_section = [](const string& s) { cerr << "--- " << s << " ---\n"; };
    
    auto debug_var = [](auto val, const string& name) {
        cerr << name << " = " << val << "\n";
    };
    auto debug_vars = [](auto v1, auto v2, const string& n1, const string& n2) {
        cerr << n1 << " = " << v1 << ", " << n2 << " = " << v2 << "\n";
    };
    auto debug_vars3 = [](auto v1, auto v2, auto v3, const string& n1, const string& n2, const string& n3) {
        cerr << n1 << " = " << v1 << ", " << n2 << " = " << v2 << ", " << n3 << " = " << v3 << "\n";
    };
    auto debug_vars4 = [](auto v1, auto v2, auto v3, auto v4, const string& n1, const string& n2, const string& n3, const string& n4) {
        cerr << n1 << " = " << v1 << ", " << n2 << " = " << v2 << ", " << n3 << " = " << v3 << ", " << n4 << " = " << v4 << "\n";
    };
    
    auto debug_vec = [](const vector<int>& v, const string& name) {
        cerr << name << ": [";
        for (int i = 0; i < v.size(); i++) {
            if (i) cerr << ", ";
            cerr << v[i];
        }
        cerr << "]\n";
    };
    auto debug_vec_long = [](const vector<long long>& v, const string& name) {
        cerr << name << ": [";
        for (int i = 0; i < v.size(); i++) {
            if (i) cerr << ", ";
            cerr << v[i];
        }
        cerr << "]\n";
    };
    auto debug_vec_char = [](const vector<char>& v, const string& name) {
        cerr << name << ": [";
        for (int i = 0; i < v.size(); i++) {
            if (i) cerr << ", ";
            cerr << v[i];
        }
        cerr << "]\n";
    };
    auto debug_vec_bool = [](const vector<bool>& v, const string& name) {
        cerr << name << ": [";
        for (int i = 0; i < v.size(); i++) {
            if (i) cerr << ", ";
            cerr << (v[i] ? 1 : 0);
        }
        cerr << "]\n";
    };
    auto debug_vec_string = [](const vector<string>& v, const string& name) {
        cerr << name << ": [\n";
        for (int i = 0; i < v.size(); i++) {
            cerr << "  [" << i << "]: \"" << v[i] << "\"\n";
        }
        cerr << "]\n";
    };
    auto debug_vec_pair = [](const vector<pair<int,int>>& v, const string& name) {
        cerr << name << ": [";
        for (int i = 0; i < v.size(); i++) {
            if (i) cerr << ", ";
            cerr << "(" << v[i].first << "," << v[i].second << ")";
        }
        cerr << "]\n";
    };
    
    
    auto debug_vec2d = [](const vector<vector<int>>& v, const string& name) {
        cerr << name << ":\n";
        for (int i = 0; i < v.size(); i++) {
            cerr << "  [" << i << "]: [";
            for (int j = 0; j < v[i].size(); j++) {
                if (j) cerr << ", ";
                cerr << v[i][j];
            }
            cerr << "]\n";
        }
    };
    auto debug_vec2d_long = [](const vector<vector<long long>>& v, const string& name) {
        cerr << name << ":\n";
        for (int i = 0; i < v.size(); i++) {
            cerr << "  [" << i << "]: [";
            for (int j = 0; j < v[i].size(); j++) {
                if (j) cerr << ", ";
                cerr << v[i][j];
            }
            cerr << "]\n";
        }
    };
    auto debug_vec2d_char = [](const vector<vector<char>>& v, const string& name) {
        cerr << name << ":\n";
        for (int i = 0; i < v.size(); i++) {
            cerr << "  [" << i << "]: ";
            for (int j = 0; j < v[i].size(); j++) {
                cerr << v[i][j];
            }
            cerr << "\n";
        }
    };
    
    
    auto debug_arr = [](const int arr[], int n, const string& name) {
        cerr << name << ": [";
        for (int i = 0; i < n; i++) {
            if (i) cerr << ", ";
            cerr << arr[i];
        }
        cerr << "]\n";
    };
    auto debug_state = [](const array<long long, 4>& cnt) {
        cerr << "State: [" << cnt[0] << ", " << cnt[1] << ", " << cnt[2] << ", " << cnt[3] << "]\n";
    };
    auto debug_array3 = [](const array<int, 3>& arr, const string& name) {
        cerr << name << ": [" << arr[0] << ", " << arr[1] << ", " << arr[2] << "]\n";
    };
    auto debug_array4 = [](const array<int, 4>& arr, const string& name) {
        cerr << name << ": [" << arr[0] << ", " << arr[1] << ", " << arr[2] << ", " << arr[3] << "]\n";
    };
    
    
    auto debug_set = [](const set<int>& s, const string& name) {
        cerr << name << ": {";
        int cnt = 0;
        for (int x : s) {
            if (cnt++) cerr << ", ";
            cerr << x;
        }
        cerr << "}\n";
    };
    auto debug_multiset = [](const multiset<int>& s, const string& name) {
        cerr << name << ": {";
        int cnt = 0;
        for (int x : s) {
            if (cnt++) cerr << ", ";
            cerr << x;
        }
        cerr << "}\n";
    };
    auto debug_map = [](const map<int,int>& m, const string& name) {
        cerr << name << ": {\n";
        for (auto [k, v] : m) {
            cerr << "  " << k << " -> " << v << "\n";
        }
        cerr << "}\n";
    };
    auto debug_unordered_map = [](const unordered_map<int,int>& m, const string& name) {
        cerr << name << ": {\n";
        for (auto [k, v] : m) {
            cerr << "  " << k << " -> " << v << "\n";
        }
        cerr << "}\n";
    };
    
    
    auto debug_pair = [](const pair<int,int>& p, const string& name) {
        cerr << name << ": (" << p.first << ", " << p.second << ")\n";
    };
    auto debug_pair_long = [](const pair<long long, long long>& p, const string& name) {
        cerr << name << ": (" << p.first << ", " << p.second << ")\n";
    };
    auto debug_tuple3 = [](const tuple<int,int,int>& t, const string& name) {
        cerr << name << ": (" << get<0>(t) << ", " << get<1>(t) << ", " << get<2>(t) << ")\n";
    };
    
    
    auto debug_queue = [](queue<int> q, const string& name) {
        cerr << name << " (front to back): [";
        int cnt = 0;
        while (!q.empty()) {
            if (cnt++) cerr << ", ";
            cerr << q.front();
            q.pop();
        }
        cerr << "]\n";
    };
    auto debug_stack = [](stack<int> s, const string& name) {
        cerr << name << " (top to bottom): [";
        int cnt = 0;
        while (!s.empty()) {
            if (cnt++) cerr << ", ";
            cerr << s.top();
            s.pop();
        }
        cerr << "]\n";
    };
    auto debug_pq = [](priority_queue<int> pq, const string& name) {
        cerr << name << " (max to min): [";
        int cnt = 0;
        while (!pq.empty()) {
            if (cnt++) cerr << ", ";
            cerr << pq.top();
            pq.pop();
        }
        cerr << "]\n";
    };
    auto debug_pq_min = [](priority_queue<int, vector<int>, greater<int>> pq, const string& name) {
        cerr << name << " (min to max): [";
        int cnt = 0;
        while (!pq.empty()) {
            if (cnt++) cerr << ", ";
            cerr << pq.top();
            pq.pop();
        }
        cerr << "]\n";
    };
    
    
    auto debug_deque = [](const deque<int>& dq, const string& name) {
        cerr << name << ": [";
        for (int i = 0; i < dq.size(); i++) {
            if (i) cerr << ", ";
            cerr << dq[i];
        }
        cerr << "]\n";
    };
    
    
    auto debug_string = [](const string& s, const string& name) {
        cerr << name << ": \"" << s << "\"\n";
    };
    auto debug_string_chars = [](const string& s, const string& name) {
        cerr << name << " (chars): [";
        for (int i = 0; i < s.size(); i++) {
            if (i) cerr << ", ";
            cerr << "'" << s[i] << "'";
        }
        cerr << "]\n";
    };
    auto debug_string_ascii = [](const string& s, const string& name) {
        cerr << name << " (ASCII): [";
        for (int i = 0; i < s.size(); i++) {
            if (i) cerr << ", ";
            cerr << (int)s[i];
        }
        cerr << "]\n";
    };
    
    
    auto debug_grid = [](const vector<string>& grid, const string& name) {
        cerr << name << " (" << grid.size() << "x" << (grid.empty() ? 0 : grid[0].size()) << "):\n";
        for (int i = 0; i < grid.size(); i++) {
            cerr << "  " << grid[i] << "\n";
        }
    };
    auto debug_grid_indexed = [](const vector<string>& grid, const string& name) {
        cerr << name << " (" << grid.size() << "x" << (grid.empty() ? 0 : grid[0].size()) << "):\n";
        for (int i = 0; i < grid.size(); i++) {
            cerr << "  [" << i << "]: " << grid[i] << "\n";
        }
    };
    
    
    auto debug_adj_list = [](const vector<vector<int>>& adj, const string& name) {
        cerr << name << " (adjacency list):\n";
        for (int i = 0; i < adj.size(); i++) {
            cerr << "  " << i << " -> [";
            for (int j = 0; j < adj[i].size(); j++) {
                if (j) cerr << ", ";
                cerr << adj[i][j];
            }
            cerr << "]\n";
        }
    };
    auto debug_edge_list = [](const vector<pair<int,int>>& edges, const string& name) {
        cerr << name << " (edge list):\n";
        for (int i = 0; i < edges.size(); i++) {
            cerr << "  Edge " << i << ": " << edges[i].first << " -- " << edges[i].second << "\n";
        }
    };
    auto debug_weighted_adj = [](const vector<vector<pair<int,int>>>& adj, const string& name) {
        cerr << name << " (weighted adjacency list):\n";
        for (int i = 0; i < adj.size(); i++) {
            cerr << "  " << i << " -> [";
            for (int j = 0; j < adj[i].size(); j++) {
                if (j) cerr << ", ";
                cerr << "(" << adj[i][j].first << "," << adj[i][j].second << ")";
            }
            cerr << "]\n";
        }
    };
    
    
    auto debug_range = [](int l, int r, const string& name) {
        cerr << name << ": [" << l << ", " << r << "]\n";
    };
    auto debug_range_values = [](const vector<int>& v, int l, int r, const string& name) {
        cerr << name << "[" << l << ".." << r << "]: [";
        for (int i = l; i <= r && i < v.size(); i++) {
            if (i > l) cerr << ", ";
            cerr << v[i];
        }
        cerr << "]\n";
    };
    
    
    auto debug_compare = [](auto a, auto b, const string& op) {
        cerr << "Compare: " << a << " " << op << " " << b << " = " << (op == "==" ? (a == b) : op == "!=" ? (a != b) : op == "<" ? (a < b) : op == "<=" ? (a <= b) : op == ">" ? (a > b) : (a >= b)) << "\n";
    };
    
    
    auto debug_if = [](bool condition, const string& msg) {
        if (condition) cerr << "✓ TRUE: " << msg << "\n";
        else cerr << "✗ FALSE: " << msg << "\n";
    };
    auto debug_assert = [](bool condition, const string& msg) {
        cerr << "[ASSERT] " << msg << ": " << (condition ? "PASS" : "FAIL") << "\n";
        if (!condition) cerr << "  ^^^ ASSERTION FAILED ^^^\n";
    };
    
    
    auto debug_iteration = [](int iter, int total) {
        cerr << "Iteration " << iter << " / " << total << "\n";
    };
    auto debug_loop_start = [](const string& name) {
        cerr << ">>> Starting loop: " << name << "\n";
    };
    auto debug_loop_end = [](const string& name) {
        cerr << "<<< Ending loop: " << name << "\n";
    };
    auto debug_iteration_vars = [](int i, int j, const string& extra = "") {
        cerr << "  i=" << i << ", j=" << j;
        if (!extra.empty()) cerr << ", " << extra;
        cerr << "\n";
    };
    
    
    auto debug_function_enter = [](const string& fname) {
        cerr << ">> Enter function: " << fname << "\n";
    };
    auto debug_function_exit = [](const string& fname) {
        cerr << "<< Exit function: " << fname << "\n";
    };
    auto debug_return = [](auto val, const string& fname) {
        cerr << "<< Return from " << fname << ": " << val << "\n";
    };
    
    
    auto debug_checkpoint = [](int num) {
        cerr << "[CHECKPOINT " << num << "]\n";
    };
    auto debug_checkpoint_msg = [](int num, const string& msg) {
        cerr << "[CHECKPOINT " << num << ": " << msg << "]\n";
    };
    auto debug_marker = [](const string& marker) {
        cerr << "[MARKER: " << marker << "]\n";
    };
    
    
    auto debug_time = []() {
        cerr << "Time: " << clock() / (double)CLOCKS_PER_SEC << "s\n";
    };
    auto debug_time_start = [](const string& name) {
        cerr << "Start timing: " << name << " at " << clock() << "\n";
    };
    auto debug_time_end = [](const string& name, clock_t start) {
        cerr << "End timing: " << name << " - " << (clock() - start) / (double)CLOCKS_PER_SEC << "s\n";
    };
    
    
    auto debug_sizeof = [](const string& type, size_t sz) {
        cerr << "sizeof(" << type << ") = " << sz << " bytes\n";
    };
    auto debug_vec_capacity = [](const vector<int>& v, const string& name) {
        cerr << name << ".size() = " << v.size() << ", .capacity() = " << v.capacity() << "\n";
    };
    
    
    auto debug_sum = [](const vector<int>& v, const string& name) {
        long long sum = 0;
        for (int x : v) sum += x;
        cerr << "sum(" << name << ") = " << sum << "\n";
    };
    auto debug_min_max = [](const vector<int>& v, const string& name) {
        if (v.empty()) {
            cerr << name << " is empty\n";
            return;
        }
        int mn = *min_element(v.begin(), v.end());
        int mx = *max_element(v.begin(), v.end());
        cerr << "min(" << name << ") = " << mn << ", max(" << name << ") = " << mx << "\n";
    };
    auto debug_count = [](const vector<int>& v, int target, const string& name) {
        int cnt = count(v.begin(), v.end(), target);
        cerr << "count(" << name << ", " << target << ") = " << cnt << "\n";
    };
    
    
    auto debug_binary = [](int n, const string& name) {
        cerr << name << " = " << n << " = 0b";
        for (int i = 31; i >= 0; i--) {
            cerr << ((n >> i) & 1);
            if (i % 4 == 0 && i > 0) cerr << "_";
        }
        cerr << "\n";
    };
    auto debug_bits = [](int n) {
        cerr << "Bits: " << __builtin_popcount(n) << "\n";
    };
    
    
    auto debug_testcase = [](int tc) {
        cerr << "\n========== TEST CASE " << tc << " ==========\n";
    };
    auto debug_testcase_end = [](int tc) {
        cerr << "========== END TEST CASE " << tc << " ==========\n\n";
    };
    
    
    auto debug_dp_table = [](const vector<vector<int>>& dp, const string& name) {
        cerr << name << " (DP table):\n";
        cerr << "    ";
        for (int j = 0; j < (dp.empty() ? 0 : dp[0].size()); j++) {
            cerr << setw(4) << j;
        }
        cerr << "\n";
        for (int i = 0; i < dp.size(); i++) {
            cerr << setw(3) << i << ":";
            for (int j = 0; j < dp[i].size(); j++) {
                cerr << setw(4) << dp[i][j];
            }
            cerr << "\n";
        }
    };
    
    
    auto debug_segment = [](int node, int l, int r, auto val) {
        cerr << "Node " << node << " [" << l << ", " << r << "]: " << val << "\n";
    };
    
    
    auto debug_visit = [](int node, int dist) {
        cerr << "Visit node " << node << " at distance " << dist << "\n";
    };
    auto debug_parent = [](int node, int par) {
        cerr << "Parent of " << node << " is " << par << "\n";
    };
    auto debug_level = [](int node, int level) {
        cerr << "Node " << node << " at level " << level << "\n";
    };
    
    
    auto debug_union = [](int a, int b) {
        cerr << "Union: " << a << " <-> " << b << "\n";
    };
    auto debug_find = [](int node, int root) {
        cerr << "Find(" << node << ") = " << root << "\n";
    };
    auto debug_components = [](int cnt) {
        cerr << "Number of components: " << cnt << "\n";
    };
    
    
    auto debug_msg = [](const string& msg) {
        cerr << msg << "\n";
    };
    auto debug_msg_inline = [](const string& msg) {
        cerr << msg;
    };
    
    
    auto debug_multiline_start = [](const string& title) {
        cerr << "╔═══ " << title << " ═══\n";
    };
    auto debug_multiline_line = [](const string& line) {
        cerr << "║ " << line << "\n";
    };
    auto debug_multiline_end = []() {
        cerr << "╚═══════════════════\n";
    };
    
    #endif
    
    // Your solution code here
    
    return 0;
}
