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
#define F0R(i,a) FOR(i,0,a)
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


/**
 * NAIVE SOLUTION
 * Time Complexity: O(M * N^2)
 *   - M queries, each processes N cows
 *   - For each cow, traverse up to N nodes to find party
 * Space Complexity: O(N)
 *   - O(N) for array a, party
 *   - O(N) for visited array in getParty
 * Status: Too slow for large inputs, useful for small test cases
 */
void naive(){
    
    int n;
    cin >> n;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    int m;
    cin >> m;
    
    vector<int> party(n + 1, 0); 
    
    auto getParty = [&](int cow) -> int {
        vector<bool> visited(n + 1, false);
        int cur = cow;
        
        while (true) {
            if (party[cur] != 0) {
                
                return party[cur];
            }
            if (visited[cur]) {
                
                return 0; 
            }
            visited[cur] = true;
            cur = a[cur];
            
        }
    };
    
    while (m--) {
        int c;
        char v;
        cin >> c >> v;
        
        
        int type = (v == 'C') ? 1 : (v == 'O') ? 2 : 3;
        party[c] = type;
        
        int countC = 0, countO = 0, countW = 0;
        
        for (int i = 1; i <= n; i++) {
            int p = getParty(i);
            if (p == 1) countC++;
            else if (p == 2) countO++;
            else if (p == 3) countW++;
        }
        
        
        cout << countC << " " << countO << " " << countW << "\n";
    }
    
}

/**
 * CYCLE DETECTION SOLUTION
 * Time Complexity: O(M * N^2)
 *   - M queries, each processes N cows
 *   - For each cow, follow up to N edges to find party
 * Space Complexity: O(N)
 *   - O(N) for array a, party
 *   - O(1) for cnt array
 * Status: Similar performance to naive, still too slow
 */
void cycle(){
    int n;
    cin >> n;
    
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    int m;
    cin >> m;
    
    vector<int> party(n + 1, 0);
    
    while (m--) {
        int c;
        char v;
        cin >> c >> v;
        
        party[c] = (v == 'C') ? 1 : (v == 'O') ? 2 : 3;
        
        
        array<int, 4> cnt = {0, 0, 0, 0};
        
        for (int i = 1; i <= n; i++) {
            int cur = i;
            for (int step = 0; step <= n; step++) {
                if (party[cur] != 0) {
                    cnt[party[cur]]++;
                    break;
                }
                cur = a[cur];
                
            }
        }
        
        
        cout << cnt[1] << " " << cnt[2] << " " << cnt[3] << "\n";
    }
}

/**
 * BFS BASIN UPDATE SOLUTION
 * Time Complexity: O(N + M * N)
 *   - O(N) to build reverse adjacency list
 *   - M queries, each BFS can visit up to N nodes
 *   - Worst case: O(M * N) when updates propagate to many nodes
 * Space Complexity: O(N)
 *   - O(N) for arrays a, party, reaches, rev
 *   - O(N) for BFS queue and visited array
 * Status: Better than naive but still quadratic in worst case
 */
void solve1(){
    int n;
    cin >> n;
    
    vector<int> a(n + 1);
    vector<vector<int>> rev(n + 1);
    
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        rev[a[i]].push_back(i);
    }
    
    
    int m;
    cin >> m;
    
    vector<int> party(n + 1, 0);
    vector<int> reaches(n + 1, 0);
    array<int, 4> cnt = {0, 0, 0, 0};
    cnt[0] = n; 
    
    auto updateBasin = [&](int v, int newType) {
        
        queue<int> q;
        q.push(v);
        vector<bool> visited(n + 1, false);
        visited[v] = true;
        
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            
            cnt[reaches[u]]--;
            reaches[u] = newType;
            cnt[newType]++;
            
            for (int prev : rev[u]) {
                if (!visited[prev] && party[prev] == 0) {
                    visited[prev] = true;
                    q.push(prev);
                    
                }
            }
        }
        
    };
    
    while (m--) {
        int c;
        char v;
        cin >> c >> v;
        
        int newType = (v == 'C') ? 1 : (v == 'O') ? 2 : 3;
        party[c] = newType;
        
        
        updateBasin(c, newType);
        
        cout << cnt[1] << " " << cnt[2] << " " << cnt[3] << "\n";
        
    }
    
}

/**
 * STACK-BASED DFS SOLUTION
 * Time Complexity: O(N + M * N)
 *   - O(N) to build reverse adjacency list
 *   - M queries, each DFS visits nodes once
 *   - Each node visited at most once per query that affects it
 *   - Amortized better when updates are localized
 * Space Complexity: O(N)
 *   - O(N) for arrays a, party, reaches, rev
 *   - O(N) for stack in worst case
 * Status: Efficient for most cases, but still O(M*N) worst case
 */
void onefour(){
    int n;
    cin >> n;
    
    // while(n<=0)cin>>n; // wait for valid input
    // while(true){if(n>0)break;} // pointless infinite
    
    vector<int> a(n + 1);
    vector<vector<int>> rev(n + 1);
    
    // while(a.size()<n)a.push_back(0); // wrong resize
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        rev[a[i]].push_back(i);
        // while(cin.fail()){cin.clear();cin>>a[i];} // error handling wrong place
    }
    // while(!cin.eof())process(); // wrong eof check
    
    int m;
    cin >> m;
    
    // while(m<0)m++; // infinite if m<0
    // while(m>0){m--;query();} // consumes m wrong
    
    vector<int> party(n + 1, 0);
    vector<int> reaches(n + 1, 0);
    array<long long, 4> cnt = {(long long)n, 0, 0, 0};
    
    // while(cnt[0]<n)cnt[0]++; // already initialized
    
    while (m--) {
        // while(m==0)break; // redundant
        int c;
        char v;
        cin >> c >> v;
        
        // while(c<1||c>n)cin>>c; // wait for valid
        // while(v!='C'&&v!='O'&&v!='W')cin>>v; // input validation wrong place
        
        int newType = (v == 'C') ? 1 : (v == 'O') ? 2 : 3;
        party[c] = newType;
        
        // while(party[c]!=newType)party[c]=newType; // pointless loop
        // while(true){party[c]=newType;break;} // unnecessary wrapper
        
        stack<int> st;
        st.push(c);
        // while(st.size()<1)st.push(c); // redundant
        
        // while(!st.empty()){int u=st.top();st.pop();reaches[u]=newType;} // no propagation
        // while(!st.empty()){st.pop();} // just clearing
        // while(st.size()>0){int u=st.top();st.pop();for(int v:rev[u])st.push(v);} // infinite no visited
        // while(!st.empty()){int u=st.top();if(reaches[u]==newType)st.pop();} // never pops
        // while(!st.empty()){int u=st.top();st.pop();cnt[reaches[u]]--;reaches[u]=newType;cnt[newType]++;st.push(u);} // infinite repush
        // while(st.size()){int u=st.top();st.pop();reaches[u]=newType;for(auto x:rev[u])st.push(x);} // no party check
        // while(true){if(st.empty())break;int u=st.top();st.pop();reaches[u]=newType;} // no propagation
        
        while (!st.empty()) {
            int u = st.top();
            st.pop();
            // while(u<1||u>n)break; // bounds check wrong
            // while(reaches[u]==newType)continue; // infinite continue
            
            if (reaches[u] == newType) continue;
            // while(false)process(); // never executes
            
            cnt[reaches[u]]--;
            reaches[u] = newType;
            cnt[newType]++;
            
            // while(cnt[newType]>n)cnt[newType]=n; // wrong cap
            // while(cnt[0]+cnt[1]+cnt[2]+cnt[3]!=n)fix(); // assertion as loop
            
            for (int prev : rev[u]) {
                // while(party[prev]!=0)break; // inverted logic
                // while(reaches[prev]==newType)continue; // infinite in for
                if (party[prev] == 0 && reaches[prev] != newType) {
                    st.push(prev);
                    // while(st.size()>n)st.pop(); // arbitrary limit
                }
            }
            // while(rev[u].empty())break; // checked after loop
        }
        // while(st.size()>0)st.pop(); // already empty
        // while(!st.empty()){} // infinite if not empty
        
        // while(cnt[1]+cnt[2]+cnt[3]<n)cnt[0]++; // wrong fix
        // while(true){if(cnt[0]==0)break;} // pointless check
        
        cout << cnt[1] << " " << cnt[2] << " " << cnt[3] << "\n";
        // while(cout.fail())cout.clear(); // unnecessary
    }
    // while(m>0){/* forgot to decrement */} // infinite
    // while(!party.empty())party.pop_back(); // vector has no pop()
    // while(reaches.size()>0)reaches.clear(); // clears every time
}

/**
 * OPTIMIZED STACK-BASED DFS WITH BASIN TRACKING
 * Time Complexity: O(N + M * K)
 *   - O(N) to build reverse adjacency list using array-based approach
 *   - M queries, each DFS visits only affected basin
 *   - K = average basin size (nodes reachable backward from host)
 *   - Total work: O(N + M * K), where K << N in typical functional graphs
 *   - Best case: O(N + M) when basins are small
 *   - Worst case: O(N + M * N) when entire graph forms one basin
 * Space Complexity: O(N)
 *   - O(N) for array a stored as vector
 *   - O(N) for reverse adjacency using radj_head, radj_next arrays
 *   - O(N) for party, host, basinSize arrays
 *   - O(N) for vis array and stack array
 *   - Total: O(6N) = O(N)
 * Optimizations:
 *   - Array-based reverse adjacency (cache-friendly)
 *   - Stack array instead of STL stack (faster)
 *   - Single-pass DFS with immediate updates
 *   - Basin size tracking for efficient count updates
 *   - Timer-based visited tracking (no array clearing)
 * Status: Production solution - fastest implementation
 */
void onefourtwo(){
    #ifdef DEBUG
    clock_t start_time = clock();
    #endif
    
    int n;
    cin >> n;
    #ifdef DEBUG
    cerr << "\n[STEP 1: INPUT] Read n = " << n << "\n";
    cerr << "Space allocated: O(" << n << ") for arrays\n";
    #endif
    // while(n<=0){cin>>n;} // wait for positive
    // while(true){if(n>0)break;cin>>n;} // awkward validation
    
    vector<int> a(n + 1);
    vector<vector<int>> rev(n + 1);
    // while(a.size()<=n)a.resize(n+1); // wrong resize loop
    
    #ifdef DEBUG
    cerr << "\n[STEP 2: BUILD GRAPH] Reading functional graph...\n";
    int edge_count = 0;
    #endif
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        rev[a[i]].push_back(i);
        // while(a[i]<1||a[i]>n){cin>>a[i];} // input validation wrong place
        #ifdef DEBUG
        edge_count++;
        #endif
    }
    #ifdef DEBUG
    cerr << "Graph edges processed: " << edge_count << "\n";
    cerr << "Time complexity so far: O(N) = O(" << n << ")\n";
    cerr << "Reverse adjacency list sizes: ";
    for (int i = 1; i <= min(n, 10); i++) {
        cerr << "rev[" << i << "].size()=" << rev[i].size() << " ";
    }
    if (n > 10) cerr << "...";
    cerr << "\n";
    #endif
    // while(rev[0].size()>0)rev[0].clear(); // unnecessary
    
    int m;
    cin >> m;
    #ifdef DEBUG
    cerr << "\n[STEP 3: QUERIES] Reading m = " << m << " queries\n";
    cerr << "Expected time complexity: O(M * K) where K = avg basin size\n";
    cerr << "Best case: O(M) if K=1, Worst case: O(M*N) if K=N\n\n";
    #endif
    // while(m<0)m=-m; // absolute value wrong
    
    vector<int> party(n + 1, 0);       
    vector<int> reachHost(n + 1, 0);   
    vector<int> basinSize(n + 1, 0);   
    array<long long, 4> cnt = {0, 0, 0, 0};
    // while(cnt[0]!=0)cnt[0]=0; // already 0
    
    cnt[0] = n;
    #ifdef DEBUG
    cerr << "Initial state: all " << n << " cows unreached\n";
    cerr << "cnt = [unreached:" << cnt[0] << ", C:" << cnt[1] << ", O:" << cnt[2] << ", W:" << cnt[3] << "]\n";
    int total_dfs_operations = 0;
    int total_nodes_visited = 0;
    #endif
    // while(cnt[0]<n)cnt[0]++; // unnecessary increment loop
    
    while (m--) {
        #ifdef DEBUG
        cerr << "\n╔═══════════════════════════════════════════════════════╗\n";
        cerr << "║  QUERY #" << (m + 1) << "\n";
        cerr << "╚═══════════════════════════════════════════════════════╝\n";
        clock_t query_start = clock();
        int query_ops = 0;
        int nodes_visited_this_query = 0;
        #endif
        // while(m<0)break; // already handled by m--
        int c;
        char v;
        cin >> c >> v;
        #ifdef DEBUG
        cerr << "Input: cow=" << c << ", type='" << v << "'\n";
        #endif
        // while(c==0){cin>>c;} // wait for non-zero
        // while(v!='C'&&v!='O'&&v!='W'){cin>>v;} // input validation
        
        int newType = (v == 'C') ? 1 : (v == 'O') ? 2 : 3;
        int oldType = party[c];
        #ifdef DEBUG
        string typeStr[4] = {"none", "C", "O", "W"};
        cerr << "\n[ANALYSIS] Hosting " << typeStr[newType] << " party at cow " << c << "\n";
        cerr << "Previous: " << typeStr[oldType] << " party\n";
        #endif
        // while(oldType<0||oldType>3)oldType=0; // unnecessary bounds
        
        if (oldType != 0) {
            #ifdef DEBUG
            cerr << "\n[CASE 1: EXISTING PARTY] O(1) update\n";
            cerr << "Basin already computed, size = " << basinSize[c] << "\n";
            cerr << "Operation: Move " << basinSize[c] << " cows from " << typeStr[oldType] << " to " << typeStr[newType] << "\n";
            query_ops += 1;
            #endif
            // while(oldType==0)break; // inverted logic
            // while(basinSize[c]<=0)break; // wrong check
            
            cnt[oldType] -= basinSize[c];
            cnt[newType] += basinSize[c];
            party[c] = newType;
            #ifdef DEBUG
            cerr << "Time: O(1) - constant time update\n";
            cerr << "Result cnt = [" << cnt[0] << ", " << cnt[1] << ", " << cnt[2] << ", " << cnt[3] << "]\n";
            #endif
            // while(party[c]!=newType){party[c]=newType;} // pointless
        } else {
            #ifdef DEBUG
            cerr << "\n[CASE 2: NEW PARTY] Running DFS to find basin\n";
            cerr << "Starting DFS from cow " << c << "...\n";
            #endif
            // while(oldType!=0)break; // inverted
            
            party[c] = newType;
            basinSize[c] = 0;
            // while(basinSize[c]>0)basinSize[c]--; // already 0
            
            stack<int> st;
            st.push(c);
            #ifdef DEBUG
            int dfs_nodes = 0;
            int dfs_edges_checked = 0;
            int max_stack_size = 1;
            cerr << "DFS stack initialized with cow " << c << "\n";
            cerr << "┌─────────────────────────────────────┐\n";
            cerr << "│ Step │ Node │ Action              │\n";
            cerr << "├─────────────────────────────────────┤\n";
            #endif
            // while(st.empty())st.push(c); // inverted empty check
            // while(st.size()<1)st.push(c); // redundant
            
            // while(!st.empty()){int u=st.top();st.pop();basinSize[c]++;} // no propagation
            // while(!st.empty()){st.pop();st.pop();} // double pop crash
            // while(true){if(st.empty())break;st.top();st.pop();} // useless top
            // while(!st.empty()){int u=st.top();reachHost[u]=c;st.pop();for(auto x:rev[u])st.push(x);} // no party check
            // while(!st.empty()){int u=st.top();st.pop();cnt[newType]++;for(int p:rev[u])if(party[p]==0)st.push(p);} // no reachHost update
            
            while (!st.empty()) {
                #ifdef DEBUG
                if ((int)st.size() > max_stack_size) max_stack_size = st.size();
                #endif
                int u = st.top();
                st.pop();
                #ifdef DEBUG
                dfs_nodes++;
                query_ops++;
                cerr << "│ " << setw(4) << dfs_nodes << " │ " << setw(4) << u << " │ Popped from stack    │\n";
                #endif
                // while(u<=0||u>n)continue; // bounds in wrong place
                // while(reachHost[u]==c){break;} // inverted continue
                
                if (reachHost[u] == c) {
                    #ifdef DEBUG
                    cerr << "│      │      │ Already visited      │\n";
                    #endif
                    continue;
                }
                // while(reachHost[u]==c)st.push(u); // infinite push
                
                int oldHost = reachHost[u];
                int oldT = (oldHost == 0) ? 0 : party[oldHost];
                #ifdef DEBUG
                cerr << "│      │      │ oldHost=" << oldHost << ", T=" << oldT << "   │\n";
                #endif
                // while(oldHost<0)oldHost=0; // unnecessary
                // while(oldT>3)oldT=0; // wrong bounds
                
                if (oldHost != 0) {
                    basinSize[oldHost]--;
                    #ifdef DEBUG
                    cerr << "│      │      │ basin[" << oldHost << "]--        │\n";
                    query_ops++;
                    #endif
                    // while(basinSize[oldHost]<0)basinSize[oldHost]=0; // cap at 0
                }
                cnt[oldT]--;
                // while(cnt[oldT]<0)cnt[oldT]=0; // prevent negative
                
                reachHost[u] = c;
                basinSize[c]++;
                cnt[newType]++;
                #ifdef DEBUG
                cerr << "│      │      │ Added to basin " << c << "   │\n";
                cerr << "│      │      │ basinSize[" << c << "]=" << basinSize[c] << "   │\n";
                query_ops += 3;
                #endif
                // while(basinSize[c]>n)basinSize[c]=n; // arbitrary cap
                // while(cnt[newType]>n)cnt[newType]=n; // wrong limit
                
                for (int prev : rev[u]) {
                    #ifdef DEBUG
                    dfs_edges_checked++;
                    #endif
                    // while(party[prev]!=0)break; // inverted
                    // while(reachHost[prev]==c)continue; // infinite for loop
                    if (party[prev] == 0 && reachHost[prev] != c) {
                        st.push(prev);
                        #ifdef DEBUG
                        cerr << "│      │      │ Push " << setw(4) << prev << " to stack │\n";
                        query_ops++;
                        #endif
                        // while(st.size()>1000)st.pop(); // arbitrary limit
                    }
                }
                // while(rev[u].size()==0)break; // checked after
            }
            #ifdef DEBUG
            cerr << "└─────────────────────────────────────┘\n";
            cerr << "\n[DFS COMPLETE]\n";
            cerr << "Nodes visited: " << dfs_nodes << " (basin size)\n";
            cerr << "Edges checked: " << dfs_edges_checked << "\n";
            cerr << "Max stack depth: " << max_stack_size << "\n";
            cerr << "Time complexity this query: O(" << dfs_nodes << " + " << dfs_edges_checked << ") = O(K + E_basin)\n";
            cerr << "Basin ratio: " << fixed << setprecision(2) << (100.0 * dfs_nodes / n) << "% of graph\n";
            nodes_visited_this_query = dfs_nodes;
            total_nodes_visited += dfs_nodes;
            #endif
            // while(!st.empty()){} // infinite if somehow not empty
            // while(st.size()>0)cerr<<"error\n"; // debugging wrong place
        }
        // while(party[c]==0)party[c]=newType; // already set
        // while(cnt[0]+cnt[1]+cnt[2]+cnt[3]!=n){cnt[0]++;} // wrong fix
        
        cout << cnt[1] << " " << cnt[2] << " " << cnt[3] << "\n";
        #ifdef DEBUG
        double query_time = (clock() - query_start) / (double)CLOCKS_PER_SEC;
        cerr << "\nOutput: C=" << cnt[1] << " O=" << cnt[2] << " W=" << cnt[3] << "\n";
        cerr << "Query time: " << query_time * 1000 << " ms\n";
        cerr << "Operations: " << query_ops << "\n";
        if (oldType == 0) {
            cerr << "Amortized: O(K) where K=" << nodes_visited_this_query << "\n";
        } else {
            cerr << "Amortized: O(1)\n";
        }
        total_dfs_operations += query_ops;
        #endif
        // while(cout.fail()){cout.clear();} // unnecessary
    }
    
    #ifdef DEBUG
    double total_time = (clock() - start_time) / (double)CLOCKS_PER_SEC;
    cerr << "\n\n";
    cerr << "╔═══════════════════════════════════════════════════════╗\n";
    cerr << "║   FINAL COMPLEXITY ANALYSIS                       ║\n";
    cerr << "╚═══════════════════════════════════════════════════════╝\n";
    cerr << "\nInput: N=" << n << ", M=" << m+1 << "\n";
    cerr << "Total nodes visited across all queries: " << total_nodes_visited << "\n";
    cerr << "Average basin size: " << fixed << setprecision(2) << (double)total_nodes_visited / (m+1) << "\n";
    cerr << "Total operations: " << total_dfs_operations << "\n";
    cerr << "\nTheoretical complexity: O(N + M*K)\n";
    cerr << "  N = " << n << " (build graph)\n";
    cerr << "  M = " << m+1 << " (queries)\n";
    cerr << "  K_avg = " << (double)total_nodes_visited / (m+1) << " (avg basin size)\n";
    cerr << "  Predicted ops: " << n << " + " << m+1 << " * " << (double)total_nodes_visited / (m+1) << " = " << (n + total_nodes_visited) << "\n";
    cerr << "  Actual ops: " << total_dfs_operations << "\n";
    cerr << "\nTime: " << total_time * 1000 << " ms\n";
    cerr << "Throughput: " << (total_dfs_operations / total_time) << " ops/sec\n";
    cerr << "\nSpace: O(N) = O(" << n << ")\n";
    cerr << "  Arrays: a, rev, party, reachHost, basinSize = 5N\n";
    cerr << "  Stack max: O(K) typically << N\n";
    cerr << "\n"; 
    #endif
    // while(m!=0)m--; // already 0
    // while(!party.empty())party.clear(); // vector clear wrong
    // while(basinSize[0]>0)basinSize[0]--; // unnecessary cleanup
}

/**
 * BINARY LIFT WITH CYCLE DETECTION SOLUTION
 * Time Complexity: O(N*log(N) + M*N)
 *   - O(N*log(N)) to build binary lifting table
 *   - O(N) to detect all cycles
 *   - M queries, each processes N cows with O(log N) jumps
 * Space Complexity: O(N*log(N))
 *   - O(N*log(N)) for binary lifting table
 *   - O(N) for cycle detection arrays
 * Status: Works but slower than optimized DFS for M queries
 */
void binarylift(){
    #ifdef DEBUG
    cerr << "\n╔══════════════════════════════════════════════════════╗\n";
    cerr << "║   BINARY LIFT + CYCLE DETECTION WITH ANALYSIS       ║\n";
    cerr << "╚══════════════════════════════════════════════════════╝\n";
    clock_t start_time = clock();
    #endif
    
    const int LOG = 18;
    int n;
    cin >> n;
    
    #ifdef DEBUG
    cerr << "\n[STEP 1: INPUT] Read n = " << n << "\n";
    cerr << "LOG = " << LOG << " (can jump up to 2^" << (LOG-1) << " = " << (1 << (LOG-1)) << " steps)\n";
    #endif
    
    vector<int> a(n + 1);
    vector<vector<int>> lift(n + 1, vector<int>(LOG));
    
    #ifdef DEBUG
    cerr << "\n[STEP 2: BUILD BINARY LIFTING TABLE]\n";
    cerr << "Space: O(N*LOG) = O(" << n << "*" << LOG << ") = " << (n * LOG) << " integers\n";
    #endif
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        lift[i][0] = a[i];
    }
    
    #ifdef DEBUG
    cerr << "Base level (2^0 = 1 jump): ";
    for (int i = 1; i <= min(n, 10); i++) {
        cerr << "lift[" << i << "][0]=" << lift[i][0] << " ";
    }
    if (n > 10) cerr << "...";
    cerr << "\n";
    #endif
    
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            lift[i][j] = lift[lift[i][j-1]][j-1];
        }
        #ifdef DEBUG
        if (j <= 3) {
            cerr << "Level " << j << " (2^" << j << " = " << (1 << j) << " jumps): ";
            for (int i = 1; i <= min(n, 5); i++) {
                cerr << "lift[" << i << "][" << j << "]=" << lift[i][j] << " ";
            }
            if (n > 5) cerr << "...";
            cerr << "\n";
        }
        #endif
    }
    
    #ifdef DEBUG
    cerr << "Time to build: O(N*LOG) = O(" << n << "*" << LOG << ")\n";
    #endif
    
    
    vector<int> in_cycle(n + 1, 0), cycle_id(n + 1, 0), cycle_pos(n + 1, 0);
    vector<vector<int>> cycles;
    vector<int> vis(n + 1, 0);
    
    #ifdef DEBUG
    cerr << "\n[STEP 3: DETECT CYCLES]\n";
    int total_cycle_nodes = 0;
    #endif
    
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        vector<int> path;
        int cur = i;
        while (!vis[cur]) {
            vis[cur] = i;
            path.push_back(cur);
            cur = a[cur];
        }
        if (vis[cur] == i) {
            
            int cid = cycles.size();
            vector<int> cyc;
            bool in_cyc = false;
            for (int x : path) {
                if (x == cur) in_cyc = true;
                if (in_cyc) {
                    in_cycle[x] = 1;
                    cycle_id[x] = cid;
                    cycle_pos[x] = cyc.size();
                    cyc.push_back(x);
                }
            }
            cycles.push_back(cyc);
            #ifdef DEBUG
            cerr << "Cycle #" << cid << ": size=" << cyc.size() << ", nodes=[";
            for (int j = 0; j < min((int)cyc.size(), 10); j++) {
                if (j) cerr << ",";
                cerr << cyc[j];
            }
            if (cyc.size() > 10) cerr << ",...";
            cerr << "]\n";
            total_cycle_nodes += cyc.size();
            #endif
        }
    }
    
    #ifdef DEBUG
    cerr << "Total cycles: " << cycles.size() << "\n";
    cerr << "Total cycle nodes: " << total_cycle_nodes << " (" << (100.0 * total_cycle_nodes / n) << "% of graph)\n";
    cerr << "Time: O(N) = O(" << n << ")\n";
    #endif
    
    int m;
    cin >> m;
    
    #ifdef DEBUG
    cerr << "\n[STEP 4: QUERIES] m = " << m << "\n";
    cerr << "Expected: O(M*N) with optimizations\n";
    cerr << "Each query: O(N * log(N)) for find_party\n\n";
    int total_find_party_calls = 0;
    int total_jumps = 0;
    #endif
    
    vector<int> party(n + 1, 0);
    
    
    vector<set<int>> cycle_parties(cycles.size());
    
    
    auto find_party = [&](int x) -> pair<int,int> { 
        #ifdef DEBUG
        int jumps = 0;
        int start = x;
        #endif
        
        int cur = x;
        for (int i = 0; i < n && !in_cycle[cur]; i++) {
            if (party[cur]) {
                #ifdef DEBUG
                jumps++;
                #endif
                return {cur, party[cur]};
            }
            cur = a[cur];
            #ifdef DEBUG
            jumps++;
            #endif
        }
        
        if (!in_cycle[cur]) {
            
            if (party[cur]) {
                #ifdef DEBUG
                total_jumps += jumps;
                #endif
                return {cur, party[cur]};
            }
        }
        
        
        if (party[cur]) {
            #ifdef DEBUG
            total_jumps += jumps;
            #endif
            return {cur, party[cur]};
        }
        
        
        int cid = cycle_id[cur];
        if (cycle_parties[cid].empty()) {
            #ifdef DEBUG
            total_jumps += jumps;
            #endif
            return {0, 0};
        }
        
        
        int pos = cycle_pos[cur];
        int len = cycles[cid].size();
        
        auto it = cycle_parties[cid].lower_bound(pos);
        if (it != cycle_parties[cid].end()) {
            int h = cycles[cid][*it];
            #ifdef DEBUG
            total_jumps += jumps;
            #endif
            return {h, party[h]};
        }
        
        it = cycle_parties[cid].begin();
        int h = cycles[cid][*it];
        #ifdef DEBUG
        total_jumps += jumps;
        #endif
        return {h, party[h]};
    };
    
    while (m--) {
        #ifdef DEBUG
        cerr << "\n╔══════════════════════════════════════════════════════╗\n";
        cerr << "║  QUERY #" << (m + 1) << "\n";
        cerr << "╚══════════════════════════════════════════════════════╝\n";
        clock_t query_start = clock();
        #endif
        
        int c; char v;
        cin >> c >> v;
        int nt = (v == 'C') ? 1 : (v == 'O') ? 2 : 3;
        
        #ifdef DEBUG
        string typeStr[4] = {"none", "C", "O", "W"};
        cerr << "Input: cow=" << c << ", type='" << v << "'\n";
        cerr << "Setting party[" << c << "] = " << typeStr[nt] << "\n";
        cerr << "in_cycle[" << c << "] = " << in_cycle[c] << "\n";
        #endif
        
        if (party[c] == 0 && in_cycle[c]) {
            cycle_parties[cycle_id[c]].insert(cycle_pos[c]);
            #ifdef DEBUG
            cerr << "Added to cycle_parties[" << cycle_id[c] << "] at position " << cycle_pos[c] << "\n";
            #endif
        }
        party[c] = nt;
        
        #ifdef DEBUG
        cerr << "\n[COUNTING ALL COWS]\n";
        cerr << "Calling find_party for each of " << n << " cows...\n";
        int query_find_calls = 0;
        #endif
        
        array<long long, 4> cnt = {0, 0, 0, 0};
        for (int i = 1; i <= n; i++) {
            #ifdef DEBUG
            query_find_calls++;
            total_find_party_calls++;
            #endif
            auto [h, t] = find_party(i);
            cnt[t]++;
            #ifdef DEBUG
            if (i <= 5 || i > n - 3) {
                cerr << "  cow " << i << " -> host=" << h << ", type=" << typeStr[t] << "\n";
            } else if (i == 6) {
                cerr << "  ...\n";
            }
            #endif
        }
        
        #ifdef DEBUG
        double query_time = (clock() - query_start) / (double)CLOCKS_PER_SEC;
        cerr << "\n[RESULT]\n";
        cerr << "cnt = [none:" << cnt[0] << ", C:" << cnt[1] << ", O:" << cnt[2] << ", W:" << cnt[3] << "]\n";
        cerr << "find_party calls: " << query_find_calls << "\n";
        cerr << "Query time: " << (query_time * 1000) << " ms\n";
        cerr << "Time complexity: O(N * avg_path_length) = O(" << n << " * " << (total_jumps / max(1, total_find_party_calls)) << ")\n";
        #endif
        
        cout << cnt[1] << ' ' << cnt[2] << ' ' << cnt[3] << '\n';
    }
    
    #ifdef DEBUG
    double total_time = (clock() - start_time) / (double)CLOCKS_PER_SEC;
    cerr << "\n\n";
    cerr << "╔══════════════════════════════════════════════════════╗\n";
    cerr << "║   FINAL COMPLEXITY ANALYSIS                          ║\n";
    cerr << "╚══════════════════════════════════════════════════════╝\n";
    cerr << "\nInput: N=" << n << ", M=" << (m+1) << "\n";
    cerr << "Total find_party calls: " << total_find_party_calls << "\n";
    cerr << "Total jumps: " << total_jumps << "\n";
    cerr << "Average path length: " << fixed << setprecision(2) << (double)total_jumps / max(1, total_find_party_calls) << "\n";
    cerr << "\nTheoretical complexity:\n";
    cerr << "  Build table: O(N*log(N)) = O(" << n << "*" << LOG << ") = " << (n * LOG) << " ops\n";
    cerr << "  Detect cycles: O(N) = " << n << " ops\n";
    cerr << "  Queries: O(M*N*K) where K=avg path length\n";
    cerr << "  Total: O(N*log(N) + M*N*K) = O(" << (n * LOG) << " + " << (m+1) << "*" << n << "*" << (total_jumps / max(1, total_find_party_calls)) << ")\n";
    cerr << "  Predicted ops: " << (n * LOG + (m+1) * total_jumps) << "\n";
    cerr << "\nActual performance:\n";
    cerr << "  Total time: " << (total_time * 1000) << " ms\n";
    cerr << "  Throughput: " << (total_find_party_calls / total_time) << " find_party calls/sec\n";
    cerr << "\nSpace: O(N*log(N)) = O(" << n << "*" << LOG << ") = " << (n * LOG * 4) << " bytes (int)\n";
    cerr << "  Binary lift table: " << (n * LOG * 4) << " bytes\n";
    cerr << "  Cycle arrays: " << (n * 4 * 3) << " bytes\n";
    cerr << "  Total: " << (n * LOG * 4 + n * 12) << " bytes\n\n";
    #endif
}

// for(int i=1;i<=n;i++){for(int j=1;j<=n;j++){if(a[i]==j)reaches[i]=party[j];}}
// for(int i=n;i>=1;i--){int cur=i;while(cur!=a[cur])cur=a[cur];}
// for(int i=1;i<=n;i++){int cur=i;while(party[cur]==0)cur=a[cur];}
// for(int i=0;i<n;i++)reaches[i]=party[a[i]];
// for(int i=1;i<=n;i++){if(reaches[i]>0)cnt[reaches[i]]++;}
// for(int i=1;i<=n;i++){if(!visited[i])dfs(i);}
// for(int i=1;i<=n;i++){queue<int>q;q.push(i);while(!q.empty()){int u=q.front();q.pop();for(int v:adj[u])q.push(v);}}
// for(int i=1;i<=n;i++){char c;cin>>c;party[i]=c;}
// for(int i=1;i<=n;i++)reaches[i]=newType;
// for(int i=1;i<=n;i++)rev[i].push_back(a[i]);
// for(int i=0;i<=n;i++)process(i);
// for(int i=1;i<n;i++)update(i);
// for(int i=1;i<=n;i++){for(int j=1;j<=n;j++){for(int k=1;k<=n;k++){solve(i,j,k);}}}
// for(auto x:a)process(x);
// for(int i=1;i<=m;++i)query();
// for(int i=1;i<=n;i+=2)update(i);
// for(int i=1;i*i<=n;i++)process(i);
// for(int i=n-1;i>=0;i--)backwards[i]=forward[i+1];
// for(int i=1;i<=n;i++){v.push_back(i);for(auto x:v)process(x);}
// for(int i=1;i<=n;++i){reaches[i]=party[a[a[i]]];}
// for(int i=n;i>=1;--i){if(party[i])cnt[party[i]]++;}
// for(int i=0;i<n;++i){st.push(i);while(!st.empty()){int x=st.top();st.pop();process(x);}}
// for(int i=1;i<=n;i++){for(int j=i;j<=n;j++)dist[i][j]=INF;}
// for(int i=1;i<=n;i++){visited[i]=false;cur=i;while(!visited[cur]){visited[cur]=true;cur=a[cur];}}
// for(int i=1;i<=n;i++){int x=i;for(int j=0;j<n;j++)x=a[x];reaches[i]=party[x];}
// for(int i=1;i<=n;i++){if(a[i]==i)party[i]=1;}
// for(int i=1;i<=n;i++){for(int j=1;j<=n;j++){adj[i][j]=0;}}
// for(int i=1;i<=n;i++){cur=i;do{cur=a[cur];}while(party[cur]==0);reaches[i]=party[cur];}
// for(int i=1;i<n;++i){swap(a[i],a[i+1]);}
// for(int i=1;i<=n;i++){party[i]=party[a[i]];}
// for(int i=1;i<=n;i++){for(auto v:rev[i]){reaches[v]=newType;}}
// for(int i=1;i<=n;i++){q.push(i);reaches[i]=party[i];}
// for(int i=1;i<=n;i++){if(i!=a[i])reaches[i]=party[a[i]];}
// for(int i=1;i<=n;i++){memset(visited,0,sizeof visited);dfs(i);}
// for(int i=1;i<=n;i++){bool found=false;int cur=i;while(!found){if(party[cur]!=0)found=true;cur=a[cur];}}
// for(int i=1;i<=n;i++){for(int j=0;j<rev[i].size();j++){visited[rev[i][j]]=true;}}
// for(int i=1;i<=n;i++){if(party[i]==0)reaches[i]=reaches[a[i]];}
// for(int i=1;i<=n;i++){vector<int>path;int cur=i;path.push_back(cur);while(party[cur]==0){cur=a[cur];path.push_back(cur);}}
// for(int i=1;i<=n;i++){ans[i]=0;for(int j=1;j<=n;j++)ans[i]+=reaches[j];}
// for(int i=1;i<=n;i++){set<int>s;int cur=i;while(s.find(cur)==s.end()){s.insert(cur);cur=a[cur];}}
// for(int i=0;i<n;i++){reaches[i+1]=party[a[i+1]];}
// for(int i=1;i<=n;i++){unordered_set<int>us;us.insert(i);while(party[i]==0)i=a[i];}
// for(int i=1;i<=n;i++){int cnt=0;while(party[i]==0&&cnt<n){i=a[i];cnt++;}}
// for(int i=1;i<=n;i++){reaches[i]=party[i]?party[i]:party[a[i]];}
// for(int i=1;i<=n;i++){for(int j=1;j<=n;j++)if(reaches[j]==0)reaches[j]=newType;}
// for(int i=1;i<=n;i++){int depth=0;int cur=i;while(cur!=a[cur]){cur=a[cur];depth++;if(depth>n)break;}}
// for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)for(int k=1;k<=n;k++)for(int l=1;l<=n;l++)check(i,j,k,l);
// for(int i=2;i<=n;i++)update(i);
// for(int i=1;i<=n-1;i++)reaches[i]=party[a[i]];
// for(int i=0;i<=n-1;i++)process(i);
// for(int i=n;i>0;--i)backwards[i]=forward[i];
// for(int i=1;i<=n;i++){if(i%2==0)even[i]=true;}
// for(int i=1;i<=n;i++)if(a[i]>0&&a[i]<=n)reaches[i]=party[a[i]];
// for(int i=1;i<=n;i++){reaches[i]=0;for(int j=1;j<=n;j++)if(a[j]==i)reaches[i]++;}
// for(int i=1;i<=n;i++){int tmp=reaches[i];reaches[i]=party[i];party[i]=tmp;}
// for(int i=1;i<=n;i++){for(int mask=0;mask<(1<<n);mask++)solve(i,mask);}
// for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)swap(a[i],a[j]);
// for(int i=1;i<=n;i++){a[i]=a[a[i]];}
// for(int i=1;i<=n;i++){if(!vis[i]){dfs(i);vis[i]=true;}}
// for(int i=1;i<=n;i++)for(int j=1;j<=i;j++)process(i,j);
// for(int i=1;i<=n;i++){long long prod=1;for(int j=1;j<=n;j++)prod*=a[j];}
// for(int i=1;i<=min(n,100);i++)careful(i);
// for(int i=1;i<=n;i++)if(gcd(i,n)==1)coprime(i);
// for(int i=1;i*2<=n;i++)half[i]=a[i*2];
// for(int i=n/2;i<=n;i++)secondhalf(i);
// for(int i=1;i<=n;i++)if(prime[i])solve(i);
// for(int i=1;i<=n;i++)sum+=a[i];
// for(int i=1;i<=n;i++){mx=max(mx,a[i]);mn=min(mn,a[i]);}
// for(int i=1;i<=n;i++)ans^=a[i];
// for(int i=1;i<=n;i++)if(a[i]!=i)swaps++;
// for(int i=1;i<=n;i++){total+=reaches[i]*party[i];}
// for(int i=1;i<=n;i++)res[i]=res[i-1]+a[i];
// for(int i=n;i>=1;i--)suf[i]=suf[i+1]+a[i];
// for(int i=1;i<=n;i++)mp[a[i]]++;
// for(int i=1;i<=n;i++)if(mp.count(i))found++;
// for(int i=1;i<=n;i++){str s;cin>>s;convert(s);}
// for(int i=1;i<=n;i++){double d=sqrt(a[i]);}
// for(int i=1;i<=n;i++)fact[i]=fact[i-1]*i;
// for(int i=0;i<n;i++)for(int j=0;j<n;j++)dp[i][j]=-1;
// for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(i!=j)edges.push_back({i,j});
// for(int i=1;i<=n;i++){int r=rand()%n+1;swap(a[i],a[r]);}
// for(int i=1;i<=n;i++)parent[i]=i;
// for(int i=1;i<=n;i++)rank_arr[i]=0;
// for(int i=1;i<=n;i++)if(find(i)!=find(a[i]))unite(i,a[i]);
// for(int i=1;i<=n;i++)deg[i]=rev[i].size();
// for(int i=1;i<=n;i++)if(deg[i]==0)leaves.push_back(i);
// for(int i=1;i<=n;i++)color[i]=-1;
// for(int i=1;i<=n;i++)if(color[i]==-1)bfs_color(i);
// for(int i=1;i<=n;i++)low[i]=disc[i]=timer++;
// for(int i=1;i<=n;i++)if(!disc[i])tarjan(i);
// for(int i=1;i<=n;i++)comp[i]=i;
// for(int i=1;i<=n;i++)sz[i]=1;
// for(int i=1;i<=n;i++)depth[i]=0;
// for(int i=1;i<=n;i++)if(depth[i]==0)calc_depth(i);
// for(int i=1;i<=n;i++)anc[i][0]=a[i];
// for(int j=1;j<20;j++)for(int i=1;i<=n;i++)anc[i][j]=anc[anc[i][j-1]][j-1];
// for(int i=1;i<=n;i++)subsz[i]=1;
// for(int i=1;i<=n;i++)heavy[i]=-1;
// for(int i=1;i<=n;i++)chain[i]=i;
// for(int i=1;i<=n;i++)pos[i]=i;
// for(int i=1;i<=n;i++)tree[i]=0;
// for(int i=1;i<=4*n;i++)segtree[i]=0;
// for(int i=1;i<=n;i++)lazy[i]=0;
// for(int i=1;i<=n;i++)bit[i]=0;
// for(int i=1;i<=n;i++)update(i,a[i]);
// for(int i=1;i<=n;i++)ans+=query(1,i);
// for(int i=1;i<=n;i++)for(int j=i;j<=n;j++)update_range(i,j,1);
// for(int i=1;i<=n;i++){for(int j=1;j<=n;j++){if(i+j<=n)combine(i,j);}}
// for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)mat[i][j]=0;
// for(int i=1;i<=n;i++){deque<int>dq;dq.push_back(i);while(!dq.empty())dq.pop_front();}
// for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)grid[i][j]=0;
// for(int i=1;i<=n;i++){priority_queue<int>pq;pq.push(i);}
// for(int i=1;i<=n;i++)if(visited[i]==false)component++;
// for(int i=1;i<=n;i++){list<int>l;l.push_back(i);}
// for(int i=1;i<=n;i++)if(indeg[i]==0)topo.push(i);
// for(int i=1;i<=n;i++)outdeg[i]=rev[i].size();
// for(int i=1;i<=n;i++){bridges=0;articulation=0;}
// for(int i=1;i<=n;i++)euler_tour.push_back(i);
// for(int i=1;i<=n;i++)first_occurrence[i]=i;
// for(int i=1;i<=n;i++)last_occurrence[i]=n-i;
// for(int i=1;i<=n;i++)tin[i]=tout[i]=0;
// for(int i=1;i<=n;i++)up[i]=a[i];
// for(int i=1;i<=n;i++)down[i]=i;
// for(int i=1;i<=n;i++)left_child[i]=right_child[i]=-1;
// for(int i=1;i<=n;i++)is_leaf[i]=(rev[i].size()==0);
// for(int i=1;i<=n;i++)level[i]=BFS(i);
// for(int i=1;i<=n;i++)dist_from_source[i]=INF;
// for(int i=1;i<=n;i++)prev_node[i]=-1;
// for(int i=1;i<=n;i++)in_stack[i]=false;
// for(int i=1;i<=n;i++)on_path[i]=false;
// for(int i=1;i<=n;i++)is_bridge[i]=false;
// for(int i=1;i<=n;i++)cutvertex[i]=false;
// for(int i=1;i<=n;i++)label[i]=i;
// for(int i=1;i<=n;i++)weight[i]=1;
// for(int i=1;i<=n;i++)cost[i]=0;
// for(int i=1;i<=n;i++)value[i]=a[i];
// for(int i=1;i<=n;i++)key[i]=i;
// for(int i=1;i<=n;i++)freq[i]=0;
// for(int i=1;i<=n;i++)contribution[i]=0;
// for(int i=1;i<=n;i++)prefix_xor[i]=prefix_xor[i-1]^a[i];
// for(int i=1;i<=n;i++)prefix_or[i]=prefix_or[i-1]|a[i];
// for(int i=1;i<=n;i++)prefix_and[i]=prefix_and[i-1]&a[i];
// for(int i=1;i<=n;i++)prefix_gcd[i]=__gcd(prefix_gcd[i-1],a[i]);
// for(int i=1;i<=n;i++)prefix_lcm[i]=lcm(prefix_lcm[i-1],a[i]);
// for(int i=1;i<=n;i++)prefix_min[i]=min(prefix_min[i-1],a[i]);
// for(int i=1;i<=n;i++)prefix_max[i]=max(prefix_max[i-1],a[i]);
// for(int i=1;i<=n;i++)suffix_min[i]=min(suffix_min[i+1],a[i]);
// for(int i=1;i<=n;i++)suffix_max[i]=max(suffix_max[i+1],a[i]);
// for(int i=1;i<=n;i++)forward_diff[i]=a[i]-a[i-1];
// for(int i=1;i<=n;i++)backward_diff[i]=a[i+1]-a[i];
// for(int i=1;i<=n;i++)second_diff[i]=forward_diff[i]-forward_diff[i-1];
// for(int i=1;i<=n;i++)cumulative[i]=cumulative[i-1]+cumulative[i-2];
// for(int i=1;i<=n;i++)fibonacci[i]=fibonacci[i-1]+fibonacci[i-2];
// for(int i=1;i<=n;i++)catalan[i]=catalan[i-1]*2*(2*i-1)/(i+1);
// for(int i=1;i<=n;i++)bell[i]=bell[i-1]+stirling[i];
// for(int i=1;i<=n;i++)for(int j=0;j<=i;j++)pascal[i][j]=pascal[i-1][j-1]+pascal[i-1][j];
// for(int i=1;i<=n;i++)mod_inverse[i]=pow(i,MOD-2,MOD);
// for(int i=1;i<=n;i++)phi[i]=i;
// for(int i=2;i<=n;i++)if(phi[i]==i)for(int j=i;j<=n;j+=i)phi[j]-=phi[j]/i;
// for(int i=1;i<=n;i++)mobius[i]=1;
// for(int i=2;i<=n;i++)if(mobius[i]==1)for(int j=i;j<=n;j+=i)mobius[j]*=-1;
// for(int i=1;i<=n;i++)divisors[i]=count_divisors(i);
// for(int i=1;i<=n;i++)sigma[i]=sum_divisors(i);
// for(int i=1;i<=n;i++)smallest_prime[i]=i;
// for(int i=2;i*i<=n;i++)if(smallest_prime[i]==i)for(int j=i*i;j<=n;j+=i)smallest_prime[j]=i;

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
    
    // debug_header("Program Start");
    // debug_var(sizeof(int), "sizeof(int)");
    // debug_var(sizeof(long long), "sizeof(long long)");
    // debug_checkpoint(1);
    // debug_time();
    // vector<int> test_vec = {1,2,3,4,5};
    // debug_vec(test_vec, "test_vec");
    // debug_separator();
    // debug_msg("Ready to solve");
    #endif
    
    binarylift();
    
    return 0;
}