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
struct Trie {
    vector<array<int,26>> ch;
    vector<bool> end;
    Trie() { newNode(); }
    int newNode() {
        ch.push_back({});
        ch.back().fill(-1);
        end.push_back(false);
        return ch.size() - 1;
    }
    void insert(const string& w) {
        int cur = 0;
        for (char c : w) {
            int x = c - 'a';
            if (ch[cur][x] == -1) ch[cur][x] = newNode();
            cur = ch[cur][x];
        }
        end[cur] = true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();

    int k;
    cin >> k;

    Trie trie;
    for (int i = 0; i < k; i++) {
        string w;
        cin >> w;
        trie.insert(w);
    }

    vector<long long> dp(n + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        if (dp[i] == 0) continue;
        int cur = 0;
        for (int j = i; j < n; j++) {
            int x = s[j] - 'a';
            if (trie.ch[cur][x] == -1) break;
            cur = trie.ch[cur][x];
            if (trie.end[cur]) dp[j + 1] = (dp[j + 1] + dp[i]) % MOD;
        }
    }

    cout << dp[n] << "\n";
    return 0;
}