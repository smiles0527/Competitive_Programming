#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using i128 = __int128_t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i64 N, M, A, B;
    if (!(cin >> N >> M >> A >> B)) return 0;
    vector<pair<int, char>> people;
    people.reserve(M);
    unordered_map<int, int> mask;
    mask.reserve(M * 2);
    unordered_map<int, int> cdcount;
    cdcount.reserve(M * 2);
    for (int i = 0; i < M; ++i) {
        string s;
        cin >> s;
        char ch = s.back();
        s.pop_back();
        int r = stoi(s);
        people.emplace_back(r, ch);
        int idx = (ch == 'A' ? 0 : ch == 'B' ? 1 : ch == 'C' ? 2 : ch == 'D' ? 3 : ch == 'E' ? 4 : 5);
        mask[r] |= (1 << idx);
        if (ch == 'C' || ch == 'D') cdcount[r]++;
    }
    vector<int> cd_rows;
    vector<i64> cd_pref;
    {
        vector<pair<int, int>> v(cdcount.begin(), cdcount.end());
        sort(v.begin(), v.end());
        i64 run = 0;
        for (auto& p : v) {
            cd_rows.push_back(p.first);
            run += p.second;
            cd_pref.push_back(run);
        }
    }
    auto cd_prefix = [&](int r)->i64 {
        if (r <= 0 || cd_rows.empty()) return 0;
        auto it = upper_bound(cd_rows.begin(), cd_rows.end(), r);
        if (it == cd_rows.begin()) return 0;
        size_t idx = (it - cd_rows.begin()) - 1;
        return cd_pref[idx];
        };
    i64 totalCD = cd_rows.empty() ? 0 : cd_pref.back();

    auto isLeaver = [&](int row, int idx)->bool {
        auto it = mask.find(row);
        if (it == mask.end()) return false;
        return (it->second >> idx) & 1;
        };

    vector<i64> dC, dZ;
    i64 sum_cB = 0;

    for (auto& pr : people) {
        int r = pr.first;
        char c = pr.second;
        bool cNon = !isLeaver(r, 2);
        bool dNon = !isLeaver(r, 3);
        i64 internal = 0, dup = 0;
        if (c == 'A') { if (!isLeaver(r, 1)) internal++; if (cNon) internal++; if (cNon) dup = 1; }
        else if (c == 'B') { if (cNon) internal++; if (cNon) dup = 1; }
        else if (c == 'E') { if (dNon) internal++; if (dNon) dup = 1; }
        else if (c == 'F') { if (!isLeaver(r, 4)) internal++; if (dNon) internal++; if (dNon) dup = 1; }

        i64 front_aisle = 2LL * r - cd_prefix(r);
        i64 back_aisle = 2LL * (N - r + 1) - (totalCD - cd_prefix(r - 1));

        i64 cF = internal + front_aisle - dup;
        i64 cB = internal + back_aisle - dup;

        sum_cB += cB;
        i64 di = cF - cB;

        if (c == 'C' || c == 'D') dC.push_back(di);
        else dZ.push_back(di);
    }

    sort(dC.begin(), dC.end());
    sort(dZ.begin(), dZ.end());

    vector<i64> prefC(dC.size() + 1, 0), prefZ(dZ.size() + 1, 0);
    for (size_t i = 1; i < prefC.size(); ++i) prefC[i] = prefC[i - 1] + dC[i - 1];
    for (size_t i = 1; i < prefZ.size(); ++i) prefZ[i] = prefZ[i - 1] + dZ[i - 1];

    int t = (int)dC.size();
    int zc = (int)dZ.size();

    auto stepDelta = [&](int j, int f)->i128 {
        return (i128)A * ((i128)2 * (j + f) - M + 1) + (i128)B * (i128)dZ[j];
        };

    int j = 0;
    while (j < zc && stepDelta(j, 0) < 0) ++j;

    auto Aterm = [&](i64 k)->i128 {
        i128 k1 = k, m = M;
        i128 part1 = k1 * (k1 - 1) / 2;
        i128 part2 = (m - k1) * (m - k1 - 1) / 2;
        return (i128)A * (part1 + part2);
        };

    i128 base = (i128)B * (i128)sum_cB;
    i128 best = -1;

    for (int f = 0; f <= t; ++f) {
        while (j > 0 && stepDelta(j - 1, f) >= 0) --j;
        int k = j + f;
        i128 cur = base;
        cur += Aterm(k);
        cur += (i128)B * ((i128)prefC[f] + (i128)prefZ[j] + (i128)f * (t - f));
        if (best < 0 || cur < best) best = cur;
    }

    if (best == 0) { cout << 0 << '\n'; return 0; }
    if (best < 0) {
        cout << "-1\n";
        return 0;
    }
    string out;
    while (best > 0) {
        int d = (int)(best % 10);
        out.push_back('0' + d);
        best /= 10;
    }
    reverse(out.begin(), out.end());
    cout << out << '\n';
    return 0;
}

