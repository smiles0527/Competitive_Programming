#include <bits/stdc++.h>
using namespace std;
struct Range { int l, r, id; };
bool cmp(const Range& a, const Range& b) {
    if (a.l != b.l) return a.l < b.l;
    return a.r > b.r;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<Range> a(n);
    for (int i = 0; i < n; i++) { cin >> a[i].l >> a[i].r; a[i].id = i; }
    sort(a.begin(), a.end(), cmp);
    vector<int> contains(n), contained(n);
    int mx = 0;
    for (int i = 0; i < n; i++) {
        if (a[i].r <= mx) contained[a[i].id] = 1;
        mx = max(mx, a[i].r);
    }
    int mn = INT_MAX;
    for (int i = n - 1; i >= 0; i--) {
        if (a[i].r >= mn) contains[a[i].id] = 1;
        mn = min(mn, a[i].r);
    }
    for (int i = 0; i < n; i++) cout << contains[i] << " \n"[i == n - 1];
    for (int i = 0; i < n; i++) cout << contained[i] << " \n"[i == n - 1];
}
