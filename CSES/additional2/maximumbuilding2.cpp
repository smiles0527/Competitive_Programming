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
const int INF = 1e9;

int n, m;
vector<vector<ll>> T;                                   // (n+2) x (m+3): row-1st-diff of column-2nd-diff

// step over heights (hlo,hhi], width profile P(w): flat F=B-A+1 on [1,A], ramp B-w+1 on [A+1,B]
void addContrib(int hlo, int hhi, int A, int B){
    if(hhi <= hlo) return;
    int r1 = hlo + 1, r2 = hhi; ll F = B - A + 1;
    auto app = [&](int r, int sg){
        T[r][1] += sg*F; T[r][2] -= sg*F;              // jump to F at w=1
        if(B > A){ T[r][A+1] -= sg; T[r][B+2] += sg; }  // ramp segment (slope -1) over (A,B]
        else      { T[r][A+1] -= sg*F; T[r][A+2] += sg*F; }  // no ramp: flat drops straight to 0
    };
    app(r1, +1); app(r2+1, -1);                         // fill height rows [r1,r2]
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    vector<string> g(n);
    for(auto& r : g) cin >> r;

    vector<vector<int>> up(n, vector<int>(m, 0));
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++)
        up[i][j] = g[i][j]=='*' ? 0 : (i? up[i-1][j]+1 : 1);

    T.assign(n+2, vector<ll>(m+3, 0));
    vector<array<int,4>> st; st.reserve(m+1);          // step = {htop, hbot, L, cstart}; width@c = c-L
    for(int i = 0; i < n; i++){
        st.clear();
        for(int j = 0; j < m; j++){
            int H = up[i][j], mergedL = j-1; bool needPush = true;
            while(!st.empty() && st.back()[0] > H){
                auto& E = st.back();
                if(E[1] >= H){                          // whole step vanishes at col j-1
                    int L=E[2], cs=E[3]; addContrib(E[1], E[0], cs-L, (j-1)-L);
                    mergedL = E[2]; st.pop_back();
                } else {                                // (H,htop] ends; (hbot,H] continues, same L
                    int L=E[2], cs=E[3]; addContrib(H, E[0], cs-L, (j-1)-L);
                    E[0] = H; needPush = false; break;
                }
            }
            if(needPush){ int hbot = st.empty()?0:st.back()[0]; if(H > hbot) st.push_back({H, hbot, mergedL, j}); }
        }
        while(!st.empty()){                             // flush at row end (cend = m-1)
            auto& E = st.back(); int L=E[2], cs=E[3]; addContrib(E[1], E[0], cs-L, (m-1)-L); st.pop_back();
        }
    }

    for(int h = 1; h <= n; h++) for(int w = 1; w <= m+2; w++) T[h][w] += T[h-1][w];   // prefix over heights
    string out; out.reserve((size_t)n*m*7);
    for(int h = 1; h <= n; h++){                        // double prefix over widths -> ans[h][w]
        ll d = 0, val = 0;
        for(int w = 1; w <= m; w++){ d += T[h][w]; val += d; out += to_string(val); out += ' '; }
        out += '\n';
    }
    cout << out;
}