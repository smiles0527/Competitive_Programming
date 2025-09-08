#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    if (!(cin >> N)) return 0;
    vector<int> cls[3];
    for (int i = 0; i < N; ++i) {
        int x; cin >> x;
        cls[x % 3].push_back(x);
    }
    
    int c0 = (int)cls[0].size(), c1 = (int)cls[1].size(), c2 = (int)cls[2].size();
    int T = c1 + c2;
    
    if (T == 0) {
        if (c0 == 1) { cout << cls[0][0] << "\n"; }
        else { cout << "impossible\n"; }
        return 0;
    }
    if (c0 > T + 1 || (c1 > 0 && c2 > 0 && c0 == 0)) {
        cout << "impossible\n";
        return 0;
    }
    
    vector<int> nonz;
    nonz.reserve(T);
    for (int x : cls[1]) nonz.push_back(x);
    for (int x : cls[2]) nonz.push_back(x);
    
    vector<int> slot(T + 1, 0);
    int left = c0;
    if (c1 > 0 && c2 > 0) { slot[c1] = 1; --left; }
    for (int i = 0; i <= T && left > 0; ++i) {
        if (c1 > 0 && c2 > 0 && i == c1) continue;
        slot[i] = 1; --left;
    }
    
    vector<int> res; res.reserve(N);
    int zi = 0, ni = 0;
    for (int i = 0; i <= T; ++i) {
        if (slot[i]) res.push_back(cls[0][zi++]);
        if (i < T) res.push_back(nonz[ni++]);
    }
    
    for (int i = 0; i < (int)res.size(); ++i) {
        if (i) cout << ' ';
        cout << res[i];
    }
    cout << "\n";
    return 0;
}
