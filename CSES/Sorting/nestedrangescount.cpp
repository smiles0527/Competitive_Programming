#include <bits/stdc++.h>
using namespace std;
struct Range { int l, r, id; };
bool cmp(const Range& a, const Range& b) {
    if (a.l != b.l) return a.l < b.l;
    return a.r > b.r;
}
vector<int> bit;
void add(int i, int x) { for (; i < (int)bit.size(); i += i & -i) bit[i] += x; }
int get(int i) { int ans = 0; for (; i > 0; i -= i & -i) ans += bit[i]; return ans; }
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<Range> a(n); vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].l >> a[i].r; a[i].id = i; v[i] = a[i].r;
    }
    sort(a.begin(), a.end(), cmp);
    sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());
    vector<int> contains(n), contained(n);
    bit.assign(v.size() + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        int p = lower_bound(v.begin(), v.end(), a[i].r) - v.begin() + 1;
        contains[a[i].id] = get(p); add(p, 1);
    }
    fill(bit.begin(), bit.end(), 0);
    for (int i = 0; i < n; i++) {
        int p = lower_bound(v.begin(), v.end(), a[i].r) - v.begin() + 1;
        contained[a[i].id] = i - get(p - 1); add(p, 1);
    }
    for (int i = 0; i < n; i++) cout << contains[i] << " \n"[i == n - 1];
    for (int i = 0; i < n; i++) cout << contained[i] << " \n"[i == n - 1];
}
