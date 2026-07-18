#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

int inv(const string &s){                 // B-before-A inversions; 0 <=> sorted
    int b = 0, c = 0;
    for(char ch : s){
        if(ch == 'B') b++;
        else if(ch == 'A') c += b;
    }
    return c;
}
void genNb(const string &s, vector<string> &out){
    int N = s.size(), g = s.find('.');
    for(int i = 0; i + 1 < N; i++)
        if(s[i] != '.' && s[i+1] != '.'){
            string t = s;
            t[g] = s[i]; t[g+1] = s[i+1]; t[i] = '.'; t[i+1] = '.';
            out.pb(move(t));
        }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    string st; cin >> st;

    // greedy best-first: priority (heuristic, depth) reaches goal in ~linear moves
    priority_queue<tuple<int,int,string>, vector<tuple<int,int,string>>, greater<>> pq;
    unordered_map<string,int> dist;
    unordered_map<string,string> par;

    dist[st] = 0; par[st] = "";
    pq.push({inv(st), 0, st});

    string goal;
    ll cap = 5000000;                     // node guard; real usage is tiny
    while(!pq.empty()){
        auto [h, d, u] = pq.top(); pq.pop();
        if(inv(u) == 0){ goal = u; break; }
        if(--cap < 0) break;
        vector<string> nb; genNb(u, nb);
        for(auto &v : nb){
            int nd = d + 1;
            auto it = dist.find(v);
            if(it == dist.end() || nd < it->second){
                dist[v] = nd; par[v] = u;
                pq.push({inv(v), nd, v});
            }
        }
    }

    if(goal.empty() && inv(st) != 0){ cout << -1 << '\n'; return 0; }
    if(goal.empty()) goal = st;           // already sorted

    vector<string> path;
    for(string cur = goal; cur != ""; cur = par[cur]) path.pb(cur);
    reverse(path.begin(), path.end());

    cout << path.size() - 1 << '\n';
    for(size_t i = 1; i < path.size(); i++) cout << path[i] << '\n';
}