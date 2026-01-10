#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int n;
        if (!(cin >> n) || n == 0) break;

        vector<int> a(n);
        for (int i = 0; i < n; i++) 
            cin >> a[i];

        
        vector<vector<int>> start(n), goal(n);
        for (int i = 0; i < n; i++) {
            start[i].push_back(a[i]);
            goal[i].push_back(i + 1);
        }
        
        auto encode = [&](auto &stkvec) {   
            string s;
            for (auto &stk : stkvec) {
                for (int c : stk) 
                    s += '0' + c;
                s += '|';
            }
            return s;
        };

        const string goalCode = encode(goal);
        unordered_set<string> seen;
        queue<pair<vector<vector<int>>,int>> q;

        seen.insert(encode(start));
        q.emplace(start, 0);

        int ans = -1;
        while (!q.empty()) {
            auto [st, dist] = q.front(); 
            q.pop();

            string code = encode(st);
            if (code == goalCode) {
                ans = dist;
                break;
            }

            for (int i = 0; i < n; i++) if (!st[i].empty()) {
                int v = st[i].back();
                auto base = st;
                base[i].pop_back();

                for (int d : {-1, +1}) {
                    int j = i + d;
                    if (j < 0 || j >= n) continue;
                    if (base[j].empty() || base[j].back() > v) {
                        auto nxt = base;
                        nxt[j].push_back(v);
                        string ec = encode(nxt);
                        if (seen.insert(ec).second) {
                            q.emplace(nxt, dist + 1);
                        }
                    }
                }
            }
        }

        if (ans < 0) 
            cout << "IMPOSSIBLE\n";
        else 
            cout << ans << "\n";
    }
    return 0;
}
