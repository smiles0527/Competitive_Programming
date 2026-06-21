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

const int MX = 500005;
int go[MX][26];
int fail_[MX], cnt;
ll c[MX];                               // hit counts per state

int newnode() { int u = cnt++; memset(go[u], 0, sizeof(go[u])); fail_[u] = 0; c[u] = 0; return u; }

int add(const string& p) {              // returns end-node id
    int u = 0;
    for (char ch : p) {
        int d = ch - 'a';
        if (!go[u][d]) go[u][d] = newnode();
        u = go[u][d];
    }
    return u;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string T; cin >> T;
    int k; cin >> k;

    cnt = 0; newnode();                 // root = 0
    vector<int> endId(k);
    vector<string> pat(k);
    for (int i = 0; i < k; i++) { cin >> pat[i]; endId[i] = add(pat[i]); }

    // BFS to build fail links + automaton goto; record bfs order
    vector<int> order; order.reserve(cnt);
    queue<int> q;
    for (int ch = 0; ch < 26; ch++) if (go[0][ch]) { fail_[go[0][ch]] = 0; q.push(go[0][ch]); }
    while (!q.empty()) {
        int u = q.front(); q.pop(); order.push_back(u);
        for (int ch = 0; ch < 26; ch++) {
            int v = go[u][ch];
            if (v) { fail_[v] = go[fail_[u]][ch]; q.push(v); }
            else   go[u][ch] = go[fail_[u]][ch];   // goto redirection
        }
    }

    // single pass over text: tally a hit at each visited state
    int u = 0;
    for (char ch : T) { u = go[u][ch - 'a']; c[u]++; }

    // subtree-SUM over fail tree, reverse BFS order (child before fail-parent)
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int x = order[i];
        c[fail_[x]] += c[x];
    }

    string out; out.reserve(7 * k);
    for (int i = 0; i < k; i++) { out += to_string(c[endId[i]]); out += '\n'; }
    cout << out;
    return 0;
}