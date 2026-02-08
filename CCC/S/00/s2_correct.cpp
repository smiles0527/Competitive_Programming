#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<double> s(n); for(auto &x : s)cin>>x;

    while (true) {
        int op; cin >> op;
        if(op==77)break;

        if(op==99){
            int i, p; cin >> i >> p; --i;
            double flow = s[i];
            double left = flow * p / 100.0;
            double right = flow - left;
            s[i] = left; s.insert(s.begin() + i + 1, right);
        } else {
            int i; cin >> i; --i;
            s[i] += s[i + 1];
            s.erase(s.begin() + i + 1);
        }
    }

    for (int i = 0; i < (int)s.size(); i++) { if (i) cout << ' '; cout << (long long)floor(s[i] + 0.5); }
    cout << "\n"; return 0;
}
