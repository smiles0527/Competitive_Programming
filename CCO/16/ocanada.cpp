#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N,G;
    cin>>N>>G;
    map<vector<int>, long long> cnt;
    for (int g = 0; g < G; g++) {
        vector<string> s(N);
        for (int i = 0; i < N; i++) cin >> s[i];

        vector<int> signature;
        for (int i = 0; i < N; i++) {
            int sum = 0;
            for (int j = 0; j < N; j++) if (s[i][j] == 'R') sum ^= 1;
            signature.push_back(sum);
        }
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int i = 0; i < N; i++) if (s[i][j] == 'R') sum ^= 1;
            signature.push_back(sum);
        }
        cnt[signature]++;
    }
    long long ans = 0;
    for (auto &p : cnt) {
        long long k = p.second;
        ans += k * (k - 1) / 2;
    }
    cout << ans << "\n";
}
