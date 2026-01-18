#include <bits/stdc++.h>
using namespace std;

struct Node {
    int next[26];
    int cnt;
    Node() {
        for (int i = 0; i < 26; ++i) next[i] = -1;
        cnt = 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    for (int tc = 1; tc <= T; ++tc) {
        int N;
        cin >> N;
        vector<Node> trie;
        trie.reserve(100000);
        trie.emplace_back();
        long long total = 0;
        string s;
        for (int i = 0; i < N; ++i) {
            cin >> s;
            int node = 0;
            int need = 0;
            for (int j = 0; j < (int)s.size(); ++j) {
                int c = s[j] - 'a';
                if (trie[node].next[c] == -1) {
                    trie[node].next[c] = trie.size();
                    trie.emplace_back();
                }
                node = trie[node].next[c];
                trie[node].cnt += 1;
                if (need == 0 && trie[node].cnt == 1) need = j + 1;
            }
            if (need == 0) need = s.size();
            total += need;
        }
        cout << "Case #" << tc << ": " << total << '\n';
    }
    r
