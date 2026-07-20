#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, w;                  
    cin >> n >> m >> w;
    vector<int> c(n + 1);
    for (int i = 1; i <= n; i++) cin >> c[i];

    vector<int> cnt(m + 2, 0);
    for (int i = 1; i <= n; i++) cnt[c[i]]++;
    vector<int> t(n + 1);
    for (int ty = 1, pos = 1; ty <= m; ty++)
        for (int k = 0; k < cnt[ty]; k++) t[pos++] = ty;

    // maximizing fixed points (c[i]==t[i] stay)
    vector<vector<int>> curP(m + 1), tarP(m + 1);
    for (int i = 1; i <= n; i++) if (c[i] != t[i]){
        curP[c[i]].push_back(i);
        tarP[t[i]].push_back(i);
    }
    vector<int> sig(n + 1, 0);
    for (int ty = 1; ty <= m; ty++){
        auto &A = curP[ty], &B = tarP[ty];        // |A|==|B|
        for (size_t k = 0; k < A.size(); k++) sig[A[k]] = B[k];
    }

    vector<char> vis(n + 1, 0);
    map<int, vector<vector<int>>> buk;            // len -> cycles
    for (int i = 1; i <= n; i++){
        if (c[i] == t[i] || vis[i]) continue;
        vector<int> cy; int x = i;
        while (!vis[x]){ vis[x] = 1; cy.push_back(x); x = sig[x]; }
        buk[(int)cy.size()].push_back(move(cy));
    }

    auto whole = [](vector<pair<int,int>>& R, const vector<int>& cy){
        int L = (int)cy.size();
        for (int i = 0; i < L; i++) R.push_back({cy[i], cy[(i + 1) % L]});
    };

auto chunk = [](vector<pair<int,int>>& R, const vector<int>& cy, int mm){
        for (int i = 0; i < mm - 1; i++) R.push_back({cy[i], cy[i + 1]});
        R.push_back({cy[mm - 1], cy[0]});
        vector<int> res; res.push_back(cy[0]);
        for (int i = mm; i < (int)cy.size(); i++) res.push_back(cy[i]);
        return res;
    };

    vector<vector<pair<int,int>>> rounds;
    while (!buk.empty()){
        vector<pair<int,int>> R; int cap = w;
        while (cap >= 2 && !buk.empty()){
            auto it = buk.upper_bound(cap);       // first len > cap
            if (it != buk.begin()){               // largest len <= cap: place whole
                --it;
                int L = it->first; auto &v = it->second;
                vector<int> cy = move(v.back()); v.pop_back();
                if (v.empty()) buk.erase(it);
                whole(R, cy); cap -= L;
            } else {                              // nothing fits: split biggest (> cap)
                auto jt = prev(buk.end());
                auto &v = jt->second;
                vector<int> cy = move(v.back()); v.pop_back();
                if (v.empty()) buk.erase(jt);
                vector<int> res = chunk(R, cy, cap);
                buk[(int)res.size()].push_back(move(res));
                cap = 0;
            }
        }
        if (R.empty()) break;                     // guard: w<2 with work left (unsolvable)
        rounds.push_back(move(R));
    }

    cout << rounds.size() << "\n";
    for (auto &R : rounds){
        cout << R.size();
        for (auto &p : R) cout << " " << p.first << " " << p.second;
        cout << "\n";
    }
    return 0;
}