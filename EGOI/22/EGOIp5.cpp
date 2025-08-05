#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s;
    cin >> n >> s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];  a[i] = -a[i];
    }
    sort(a.begin(), a.end());
    while (s--) {
        long long m;
        int c;
        cin >> m >> c;
        for(int i=0; i<c; i++) a[i] += m;
        inplace_merge(a.begin(), a.begin() + c, a.end());
    }
    for (int i = 0; i < n; i++) {
        cout << -a[i] << (i + 1 == n ? '\n' : ' ');
    }
    return 0;
}
