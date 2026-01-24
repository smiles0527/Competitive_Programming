#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
Imagine the N rods are nodes in a graph. The constraints (ax + ay = z) are edges connecting these circles.

We can imagine a domino effect. Inside a component, everything is locked together.
e.g. if we decide rod 1 has energy 10, and rod1 + rod2 = 100, rod2 must be 90 with no choice, then if rod2 + rod3 = 5,
rod must be -85. This means, if we pick the value for one rod in the component, all other rods are determined. We call 
that rod the 'leader'.

We represent the leader as having a value k. If the leader is +k, the neighbours are -k (to balance the equation),
this thus alternates like a checkerboard. We call this the sign, sgn.

Accounting for all the numbers (z) in the constraints, every rod has a base: every rod's value is (sgn * k + base).
Sometimes, the graph will cycle. If one loop gives a value k, but another loop gives a differnet value k', there is no 
solution so we output -1. If k = k', this group is valid, thus we calculate the total values for this component.

If there are no loops (or if they dont force a specific k), then k is free to vary. We may pick any integer for k. But,
we wish to pick the best k to maximize the number of rods within their limits.

If each rod i has a working range [lo_i, hi_i], this means we need:
    lo_i <= sgn_i * k + base_i <= hi_i
We can rewrite this to find the valid range for k:
    if sgn is posiive, k must be between [lo_i - base_i, hi_i - base_i]
    if sgn is negative, k must be between [base_i - hi_i, base_i - lo_i]

Since we are given a list of valid ranges for k 
- e.g. Rod 1 works if k is in [1, 10]
       Rod 2 works if k is in [5, 20]
       Rod 3 works if k is in [8, 12]
We need to pick a value k that is in the most intervals.    

Imagine these ranges are physical blocks stacked on a number line. We want to find the point where the stack is the highest.
- create a list of events
- for range [5, 20], add an event at (5, +1) and (21, -1)
- for range [1, 10], add an event at (1, +1) and (11, -1)
- sort the events by position
- walk through the sorted list (sweep line). Keep a running total. The highest total is the answer.


----------------------------

The question is modeled as a graph whose rods are nodes and constraints are edges.
Construct an adjacency list for the graph 
- instead of a N x N matrix (which would require 40GB for N = 2), we use a vector of edges for each node.

We run DFS on each component of the graph to assign sgn and base values to each node.
- if we revisit a node, we check if the current sgn and base values are consistent with the previous values.

Execution flow:
- push start node to stack
- process node:
    - for each edge from this node to a neighbour
        - if neighbour not visited:
            - assign sgn and base
            - push neighbour to stack
        - else:
            - check consistency
            - if inconsistent, mark fail = true and return

Sweep line:
- we transform ranges into point events
- a range [L, R] becomes two events: (L, +1) and (R+1, -1)

Sorting:
- we sort events by position
- we iterate through sorted events, maintaining a running total of active ranges

*/

struct Edge {
    int to;
    ll sum;
};

// Maximum number of nodes
const int MAXN = 200005;
// Arrays to store lower and upper limits for each rod
ll lo[MAXN], hi[MAXN];
// Adjacency list representation of the graph
vector<Edge> adj[MAXN];
// Visited array to track visited nodes during DFS
int vis[MAXN];
int sgn[MAXN];  // Stores +1 or -1
ll base[MAXN];  // Stores the constant offset

// Vector to store nodes in the current component
vector<int> nodes;
bool fail; // Flag to indicate if a contradiction is found
bool fix; // Flag to indicate if k is fixed for the component
ll k_val; // The fixed value of k if determined


// DFS
void dfs(int u) {
    nodes.push_back(u);
    
    // Explore all edges from node u
    for (auto& e : adj[u]) {
        int v = e.to;
        ll s = e.sum;
        
        // If neighbour v is not visited, assign sgn and base, then recurse
        if (!vis[v]) {
            vis[v] = 1;
            sgn[v] = -sgn[u];
            base[v] = s - base[u];
            dfs(v);
        // Else, check for consistency
        } else {
            
            // Check consistency of sgn and base values
            ll s_sum = sgn[u] + sgn[v];
            ll diff = s - base[u] - base[v];
            
            // if (sgn_u + sgn_v) == 0, then base_u + base_v must equal s
            if (s_sum == 0) {
                if (diff != 0) fail = true;
            } else {
                // Otherwise, we can solve for k
                if (abs(diff) % abs(s_sum) != 0) { // No integer solution
                    fail = true;
                } else {
                    // Calculate k
                    ll calc_k = diff / s_sum;
                    if (fix && k_val != calc_k) { 
                        fail = true; 
                    } else {
                        fix = true;
                        k_val = calc_k;
                    }
                }
            }
        }
        if (fail) return;
    }
}

void solve() {
    int N, M;
    if (!(cin >> N >> M)) return;

    // Initialize adjacency list and visited array
    for (int i = 1; i <= N; ++i) {
        adj[i].clear();
        vis[i] = 0;
    }
    // Read lower and upper limits for each rod
    for (int i = 1; i <= N; ++i) cin >> lo[i];
    for (int i = 1; i <= N; ++i) cin >> hi[i];

    // Read edges and construct the graph
    for (int i = 0; i < M; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    ll ans = 0;
    fail = false;

    // Process each component of the graph
    for (int i = 1; i <= N; ++i) {
        if (vis[i]) continue;
        nodes.clear(); 
        fix = false;
    
        vis[i] = 1;
        sgn[i] = 1; 
        base[i] = 0;
        
        dfs(i);
    
        if (fail) {
            cout << -1 << "\n";
            return;
        }
        // Calculate the answer for this component
        if (fix) {
            int cnt = 0;
            // Count valid rods with fixed k
            for (int u : nodes) {
                // compute value of rod u
                ll val = sgn[u] * k_val + base[u];
                if (val >= lo[u] && val <= hi[u]) { // Check if within limits
                    cnt++;
                }
            }
            ans += cnt;
        } else {
            // k is not fixed, use sweep line to find optimal k
            vector<pair<ll, int>> events;
            
            // Create events for each rod's valid k range
            for (int u : nodes) {
                ll l, r;
                
                // Determine valid range for k based on sgn
                if (sgn[u] == 1) {
                    l = lo[u] - base[u];
                    r = hi[u] - base[u];
                } else {
                    // sgn[u] == -1
                    l = base[u] - hi[u];
                    r = base[u] - lo[u];
                }
                
                // Add events for the range [l, r]
                if (l <= r) {
                    events.push_back({l, 1});      
                    events.push_back({r + 1, -1}); 
                }
            }
            
            // Sort events by position
            sort(events.begin(), events.end());
            
            int best = 0;
            int curr = 0;
            
            // Sweep line to find maximum overlap
            for (size_t j = 0; j < events.size(); ) {
                ll pos = events[j].first;
                
                // Process all events at the same position
                while (j < events.size() && events[j].first == pos) {
                    curr += events[j].second;
                    j++;
                }
                
                if (curr > best) {
                    best = curr;
                }
            }
            ans += best;
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
//Visit every node and edge once: O(N+M) time
//For every component without fixed k, we do a sweep line over at most 2N events: O(N log N) time
