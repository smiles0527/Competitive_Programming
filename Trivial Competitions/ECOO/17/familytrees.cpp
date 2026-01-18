#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        unordered_set<string> family;
        for (int i = 0; i < n; ++i) {
            string id;
            cin >> id;
            vector<int> parts;
            stringstream ss(id);
            string part;
            while (getline(ss, part, '.'))
                parts.push_back(stoi(part));

            for (int j = 0; j < (int)parts.size(); ++j) {
                string prefix = "0";
                for (int k = 1; k <= j; ++k) prefix += "." + to_string(parts[k]);
                family.insert(prefix);
            }

            for (int j = 1; j <= parts.back(); ++j) {
                string prefix = "0";
                for (int k = 1; k < (int)parts.size() - 1; ++k)
                    prefix += "." + to_string(parts[k]);
                prefix += "." + to_string(j);
                family.insert(prefix);
            }
        }
        cout << family.size() % MOD << "\n";
    }
}
