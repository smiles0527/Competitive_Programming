#include <bits/stdc++.h>
using namespace std;

void add_edge(vector<vector<int>>& prev, int u, int v) {
    prev[v].push_back(u);
}

int main() {

    vector<vector<int>> prev(8);

    add_edge(prev, 1, 7);
    add_edge(prev, 1, 4);
    add_edge(prev, 2, 1);
    add_edge(prev, 3, 4);
    add_edge(prev, 3, 5);

    while (true) {
        int a, b;
        cin >> a >> b;
        if (a == 0 && b == 0) break;
        add_edge(prev, a, b);
    }

    vector<int> done(8, 0);
    vector<int> order;

    for (int i = 0; i < 7; i++) {
        int p = -1;

        for (int i = 1; i <= 7; i++) {
            if (done[i]){
                continue;
            }

            bool ok = true;
            for (int u : prev[i]) {
                if (!done[u]) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                p = i;
                break;
            }
        }

        if (p == -1) {
            cout << "Cannot complete these tasks. Going to bed.\n";
            return 0;
        }

        done[p] = 1;
        order.push_back(p);
    }

    for (int i = 0; i < 7; i++) {
        if (i) cout << " ";
        cout << order[i];
    }

    cout << "\n";
}
