#include <bits/stdc++.h>
using namespace std;

static inline int B(char c){ return c=='J'; }
static inline char Cc(int b){ return b?'J':'N'; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, C;
    cin >> T >> C;
    while (T--) {
        int N; cin >> N;
        string Ls, Rs; cin >> Ls >> Rs;

        vector<int> L(N), R(N);
        int cJJ=0,cJN=0,cNJ=0,cNN=0, x=0;
        int degJ=0, degN=0;

        for (int i=0;i<N;i++){
            L[i]=B(Ls[i]); R[i]=B(Rs[i]);
            x ^= (R[i]^1);
            if (L[i]&&R[i]) cJJ++;
            else if (L[i]&&!R[i]) cJN++;
            else if (!L[i]&&R[i]) cNJ++;
            else cNN++;
            if (L[i]) degJ++; else degN++;
            if (R[i]) degJ++; else degN++;
        }

        bool ok = true;
        if (cJN != cNJ) ok = false;
        if (degJ && degN && (cJN + cNJ)==0) ok = false;
        if (x) ok = false;

        if (!ok){ cout << "NO\n"; continue; }
        cout << "YES\n";
        if (!C) continue;

        vector<int> head(2,-1), nxt(N,-1), to(N);
        for (int i=0;i<N;i++){
            int u=L[i], v=R[i];
            to[i]=v;
            nxt[i]=head[u];
            head[u]=i;
        }

        int start = (head[1]!=-1 ? 1 : 0);
        vector<int> stV; stV.reserve(N+1);
        vector<int> stE; stE.reserve(N);
        vector<int> path; path.reserve(N);
        stV.push_back(start);

        while (!stV.empty()){
            int v = stV.back();
            int &e = head[v];
            if (e!=-1){
                int id=e;
                e=nxt[id];
                stE.push_back(id);
                stV.push_back(to[id]);
            } else {
                stV.pop_back();
                if (!stE.empty()){
                    path.push_back(stE.back());
                    stE.pop_back();
                }
            }
        }
        reverse(path.begin(), path.end());

        string owners(N,'N');
        int cur=0;
        for (int k=0;k<N;k++){
            owners[k]=Cc(cur);
            cur ^= (R[path[k]]^1);
        }

        for (int i=0;i<N;i++){
            if (i) cout << ' ';
            cout << path[i]+1;
        }
        cout << "\n" << owners << "\n";
    }
}
