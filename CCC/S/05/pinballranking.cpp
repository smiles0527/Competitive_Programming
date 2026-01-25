#include <bits/stdc++.h>
using namespace std;

struct BIT {
    int n;
    vector<int> f;
    BIT(int n): n(n), f(n + 1, 0) {}
    void add(int i, int v) { for (; i <= n; i += i & -i) f[i] += v; }
    int sumPrefix(int i) { int s = 0; for (; i > 0; i -= i & -i) s += f[i]; return s; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<long long> comp = a;
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    auto idx = [&](long long x){ return int(lower_bound(comp.begin(), comp.end(), x) - comp.begin()) + 1; };
    BIT bit((int)comp.size());
    long long totalRank = 0;
    for (int i = 0; i < n; ++i) {
        int id = idx(a[i]);
        int le = bit.sumPrefix(id);
        long long greater = i - le;
        totalRank += greater + 1;
        bit.add(id, 1);
    }
    cout.setf(std::ios::fixed); 
    cout << setprecision(2) << (double)totalRank / n << "\n";
    return 0;
}
