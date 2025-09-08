#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, Q;
    if (!(cin >> N >> Q)) return 0;
    vector<long long> A(N + 1);
    for (int i = 1; i <= N; ++i) cin >> A[i];

    vector<long long> uniq(A.begin() + 1, A.end());
    sort(uniq.begin(), uniq.end());
    uniq.erase(unique(uniq.begin(), uniq.end()), uniq.end());
    unordered_map<long long,int> id;
    id.reserve(uniq.size() * 2 + 3);
    id.max_load_factor(0.7f);
    for (int i = 0; i < (int)uniq.size(); ++i) id[uniq[i]] = i;

    vector<int> comp(N + 1);
    for (int i = 1; i <= N; ++i) comp[i] = id[A[i]];
    int K = uniq.size();

    int S = N + 1;
    vector<long long> ps(1LL * S * S, 0);
    auto at = [&](int i, int j) -> long long& { return ps[1LL * i * S + j]; };

    vector<int> cnt(K), addcol(N + 1);
    for (int r = 1; r <= N; ++r) {
        fill(cnt.begin(), cnt.end(), 0);
        fill(addcol.begin(), addcol.end(), 0);
        for (int l = r - 1; l >= 1; --l) {
            cnt[comp[l + 1]]++;
            long long need = -A[l] - A[r];
            auto it = id.find(need);
            if (it != id.end()) addcol[l] = cnt[it->second];
        }
        for (int l = 1; l <= N; ++l) {
            long long add = (l < r ? addcol[l] : 0);
            at(l, r) = at(l - 1, r) + at(l, r - 1) - at(l - 1, r - 1) + add;
        }
    }

    while (Q--) {
        int a, b;
        cin >> a >> b;
        long long ans = at(b, b) - at(a - 1, b) - at(b, a - 1) + at(a - 1, a - 1);
        cout << ans << '\n';
    }
    return 0;
}
