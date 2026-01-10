#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
    
template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    ordered_set<pair<long long,int>> os;
    int uid = 0;
    for (int i = 0; i < N; i++) {
        long long x;
        cin >> x;
        os.insert({x, uid++});
    }

    long long last = 0;
    const long long MINV = 1;
    const long long MAXV = 1000000000LL;

    for (int i = 0; i < M; i++) {
        char c;
        long long enc;
        cin >> c >> enc;
        long long v = enc ^ last;

        if (c == 'I') {
            if (MINV <= v && v <= MAXV) os.insert({v, uid++});
        } else if (c == 'R') {
            if (MINV <= v && v <= MAXV) {
                auto it = os.lower_bound({v, INT_MIN});
                if (it != os.end() && it->first == v) os.erase(it);
            }
        } else if (c == 'S') {
            int k = (int)v;
            auto it = os.find_by_order(k - 1);
            long long ans = it->first;
            cout << ans << '\n';
            last = ans;
        } else if (c == 'L') {
            if (!(MINV <= v && v <= MAXV)) {
                cout << -1 << '\n';
                last = -1;
            } else {
                auto it = os.lower_bound({v, INT_MIN});
                if (it == os.end() || it->first != v) {
                    cout << -1 << '\n';
                    last = -1;
                } else {
                    int idx = (int)os.order_of_key({v, INT_MIN}) + 1;
                    cout << idx << '\n';
                    last = idx;
                }
            }
        }
    }

    bool first = true;
    for (auto &p : os) {
        if (!first) cout << ' ';
        cout << p.first;
        first = false;
    }
    cout << '\n';

    return 0;
}