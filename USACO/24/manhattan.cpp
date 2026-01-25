#include <bits/stdc++.h>
using namespace std;

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
    vector<long long> dx, dy, Sx(m+1,0), Sy(n+1,0);
    if (m >= 2) {
        dx.resize(m-1);
        for (int i = 0; i < m-1; ++i) { dx[i] = A[i+1]-A[i]; Sx[i+1] = Sx[i] + dx[i]; }
        Sx[m] = Sx[m-1];
    }
    if (n >= 2) {
        dy.resize(n-1);
        for (int j = 0; j < n-1; ++j) { dy[j] = B[j+1]-B[j]; Sy[j+1] = Sy[j] + dy[j]; }
        Sy[n] = Sy[n-1];
    }
    vector<int> nxtX, nxtY;
    if (!dx.empty()) {
        nxtX.assign(m-1, -1);
        int nxt = -1;
        for (int i = m-2; i >= 0; --i) {
            if (dx[i] & 1LL) nxt = i;
            nxtX[i] = nxt;
        }
    }
    if (!dy.empty()) {
        nxtY.assign(n-1, -1);
        int nxt = -1;
        for (int j = n-2; j >= 0; --j) {
            if (dy[j] & 1LL) nxt = j;
            nxtY[j] = nxt;
        }
    }

    while (Q--) {
        long long x, y, d;
        cin >> x >> y >> d;
        bool onV = binary_search(A.begin(), A.end(), x);
        bool onH = binary_search(B.begin(), B.end(), y);
        long long cx = x, cy = y;
        int i = -1, j = -1;
        long long D = d;
        long long t0 = 0;
        if (onV && onH) {
            i = int(lower_bound(A.begin(), A.end(), x) - A.begin());
            j = int(lower_bound(B.begin(), B.end(), y) - B.begin());
        } else if (onV) {
            i = int(lower_bound(A.begin(), A.end(), x) - A.begin());
            auto it = upper_bound(B.begin(), B.end(), y);
            if (it == B.end()) { cy += D; cout << cx << " " << cy << "\n"; continue; }
            long long ny = *it;
            t0 = ny - y;
            if (D < t0) { cy += D; cout << cx << " " << cy << "\n"; continue; }
            D -= t0;
            cy = ny;
            j = int(it - B.begin());
        } else {
            auto it = upper_bound(A.begin(), A.end(), x);
            if (it == A.end()) { cx += D; cout << cx << " " << cy << "\n"; continue; }
            long long nx = *it;
            t0 = nx - x;
            if (D < t0) { cx += D; cout << cx << " " << cy << "\n"; continue; }
            D -= t0;
            cx = nx;
            i = int(it - A.begin());
            if (!onH) {
                auto it2 = lower_bound(B.begin(), B.end(), y);
                if (it2 == B.end() || *it2 != y) {
                    j = int(upper_bound(B.begin(), B.end(), y) - B.begin());
                    cy = B[j];
                } else {
                    j = int(it2 - B.begin());
                }
            } else j = int(lower_bound(B.begin(), B.end(), y) - B.begin());
        }
        int p = int(t0 & 1LL);
        while (D > 0) {
            if (p == 0) {
                if (j >= n-1) { cy += D; D = 0; break; }
                if (nxtY.empty() || nxtY[j] == -1) { cy += D; D = 0; break; }
                long long sum = Sy[nxtY[j]] - Sy[j];
                if (D <= sum) { cy += D; D = 0; break; }
                D -= sum;
                if (D < dy[nxtY[j]]) { cy += D; D = 0; break; }
                D -= dy[nxtY[j]];
                cy = B[nxtY[j]+1];
                j = nxtY[j] + 1;
                p ^= 1;
            } else {
                if (i >= m-1) { cx += D; D = 0; break; }
                if (nxtX.empty() || nxtX[i] == -1) { cx += D; D = 0; break; }
                long long sum = Sx[nxtX[i]] - Sx[i];
                if (D <= sum) { cx += D; D = 0; break; }
                D -= sum;
                if (D < dx[nxtX[i]]) { cx += D; D = 0; break; }
                D -= dx[nxtX[i]];
                cx = A[nxtX[i]+1];
                i = nxtX[i] + 1;
                p ^= 1;
            }
        }
        cout << cx << " " << cy << "\n";
    }
    return 0;
}
