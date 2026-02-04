#include <bits/stdc++.h>
using namespace std;

static const int MAXL = 20;
static const long long INFTY = (long long)4e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, Q;
    if (!(cin >> N >> Q)) return 0;
    vector<long long> A, B;
    A.reserve(N);
    B.reserve(N);
    for (int i = 0; i < N; ++i) {
        char t; long long c;
        cin >> t >> c;
        if (t == 'V') A.push_back(c);
        else B.push_back(c);
    }
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    A.erase(unique(A.begin(), A.end()), A.end());
    B.erase(unique(B.begin(), B.end()), B.end());
    int m = (int)A.size(), n = (int)B.size();

    vector<long long> vert(m+1), horiz(n+1);
    for (int i = 0; i < m; i++) vert[i] = A[i];
    for (int j = 0; j < n; j++) horiz[j] = B[j];
    vert[m] = INFTY;
    horiz[n] = INFTY;

    vector<array<int,MAXL>> vn(m+1), hn(n+1);
    for (int t = 0; t < MAXL; t++) vn[m][t] = m, hn[n][t] = n;

    for (int i = m-1; i >= 0; --i) {
        if ((vert[i]&1) != (vert[i+1]&1)) vn[i][0] = i+1;
        else vn[i][0] = vn[i+1][0];
        for (int t = 1; t < MAXL; t++) vn[i][t] = vn[vn[i][t-1]][t-1];
    }
    for (int j = n-1; j >= 0; --j) {
        if ((horiz[j]&1) != (horiz[j+1]&1)) hn[j][0] = j+1;
        else hn[j][0] = hn[j+1][0];
        for (int t = 1; t < MAXL; t++) hn[j][t] = hn[hn[j][t-1]][t-1];
    }

    while (Q--) {
        long long x, y, d;
        cin >> x >> y >> d;

        int hlo = (int)(lower_bound(horiz.begin(), horiz.begin()+n, y) - horiz.begin());
        int vlo = (int)(lower_bound(vert.begin(), vert.begin()+m, x) - vert.begin());

        long long t = 0;

        if (y < horiz[hlo]) {
            long long need = horiz[hlo] - y;
            if (d <= need) { cout << x << " " << y + d << "\n"; continue; }
            d -= need; t += need; y = horiz[hlo];
        }
        if (x < vert[vlo]) {
            long long need = vert[vlo] - x;
            if (d <= need) { cout << x + d << " " << y << "\n"; continue; }
            d -= need; t += need; x = vert[vlo];
        }

        for (int k = MAXL-1; k >= 0; k--) {
            int h = hn[hlo][k], v = vn[vlo][k];
            long long dh = horiz[h] - horiz[hlo];
            long long dv = vert[v] - vert[vlo];
            if (dh > d) continue;
            if (dv > d) continue;
            if (dh + dv > d) continue;
            d -= dh + dv;
            t += dh + dv;
            hlo = h;
            vlo = v;
        }

        if (t & 1LL) {
            int v = vn[vlo][0];
            long long dv = vert[v] - vert[vlo];
            if (dv >= d) { cout << vert[vlo] + d << " " << horiz[hlo] << "\n"; continue; }
            d -= dv;
            cout << vert[v] << " " << horiz[hlo] + d << "\n";
        } else {
            int h = hn[hlo][0];
            long long dh = horiz[h] - horiz[hlo];
            if (dh >= d) { cout << vert[vlo] << " " << horiz[hlo] + d << "\n"; continue; }
            d -= dh;
            cout << vert[vlo] + d << " " << horiz[h] << "\n";
        }
    }
    return 0;
}
