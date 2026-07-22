#include <bits/stdc++.h>
using namespace std;
struct Customer { int a, b, id; };
bool cmp(const Customer& x, const Customer& y) {
    if (x.a != y.a) return x.a < y.a;
    return x.b < y.b;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<Customer> a(n);
    for (int i = 0; i < n; i++) { cin >> a[i].a >> a[i].b; a[i].id = i; }
    sort(a.begin(), a.end(), cmp);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    vector<int> ans(n); int rooms = 0;
    for (int i = 0; i < n; i++) {
        int room;
        if (!q.empty() && q.top().first < a[i].a) {
            room = q.top().second; q.pop();
        } else room = ++rooms;
        ans[a[i].id] = room;
        q.push({a[i].b, room});
    }
    cout << rooms << '\n';
    for (int i = 0; i < n; i++) cout << ans[i] << " \n"[i == n - 1];
}
