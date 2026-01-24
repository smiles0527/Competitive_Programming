#include <bits/stdc++.h>
using namespace std;
int idx(char c) {
    if (c <= 'Z') 
        return c - 'A';
    return 26 + (c - 'a');
}
int main() {
    int t;
    cin >> t;
    for (; t; t--) {
        string s, f;
        cin >> s >> f;

        if (s == f) {
            cout << 0 << '\n';
            continue;
        }
        int edg[52] = {0};
        for (int i = 0; i < 52; i++) 
            edg[i] = -1;
    
        bool ends[52] = {0};
        bool ok = 1;
        for (int i = 0; i < s.size(); i++) {
            int x = idx(s[i]);
            int y = idx(f[i]);
            ends[y] = 1;
            if (edg[x] != -1 && edg[x] != y) 
                ok = 0;
            edg[x] = y;
        }

        int cnt = 0;
        for (int i = 0; i < 52; i++) 
            cnt += ends[i];

        if (cnt == 52) 
            ok = 0;

        if (ok == 0) {
            cout << -1 << '\n';
            continue;
        }

        int ans = 0;
        int inDeg[52] = {0};

        for (int i = 0; i < 52; i++)
            if (edg[i] != -1 && edg[i] != i) {
                inDeg[edg[i]]++;
                ans++;
            }

        int vis[52] = {0};
        for (int i = 0; i < 52; i++)
            if (vis[i] == 0) {
                int node = i;
                while (node != -1 && vis[node] == 0) {
                    vis[node] = i + 1;
                    node = edg[node];
                }

                if (node != -1 && node != edg[node] && vis[node] == i + 1) {
                    int start = node;
                    bool pass = 0;
                    do {
                        vis[node] = 2;
                        if (inDeg[node] > 1) pass = 1;
                        node = edg[node];
                    } while (node != start);
                    if (pass == 0) 
                        ans++;
                }
            }

        cout << ans << '\n';
    }

    return 0;
}