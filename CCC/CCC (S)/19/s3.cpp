#include <bits/stdc++.h>
using namespace std;

int A[3][3];
bool isX[3][3];

void fillGrid() {
    bool cont = true;
    while (cont) {
        cont = false;
        for (int i = 0; i < 3; ++i) {
            // fill row i
            int cnt = 0, xj = -1;
            for (int j = 0; j < 3; ++j)
                if (isX[i][j]) { cnt++; xj = j; }
            if (cnt == 1) {
                int a, b;
                if (xj == 0) { a = A[i][1]; b = A[i][2]; A[i][0] = 2*a - b; }
                else if (xj == 1) { a = A[i][0]; b = A[i][2]; A[i][1] = (a + b)/2; }
                else            { a = A[i][0]; b = A[i][1]; A[i][2] = 2*b - a; }
                isX[i][xj] = false;
                cont = true;
            } else if (cnt == 3) {
                A[i][0] = A[i][1] = A[i][2] = 0;
                isX[i][0] = isX[i][1] = isX[i][2] = false;
                cont = true;
            }

            // fill column i
            cnt = 0; int xi = -1;
            for (int k = 0; k < 3; ++k)
                if (isX[k][i]) { cnt++; xi = k; }
            if (cnt == 1) {
                int a, b;
                if (xi == 0) { a = A[1][i]; b = A[2][i]; A[0][i] = 2*a - b; }
                else if (xi == 1) { a = A[0][i]; b = A[2][i]; A[1][i] = (a + b)/2; }
                else              { a = A[0][i]; b = A[1][i]; A[2][i] = 2*b - a; }
                isX[xi][i] = false;
                cont = true;
            } else if (cnt == 3) {
                A[0][i] = A[1][i] = A[2][i] = 0;
                isX[0][i] = isX[1][i] = isX[2][i] = false;
                cont = true;
            }
        }
    }
}

bool full() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (isX[i][j])
                return false;
    return true;
}

bool valid() {
    auto ok = [&](int a, int b, int c){ return c - b == b - a; };
    for (int i = 0; i < 3; ++i) {
        if (!ok(A[i][0], A[i][1], A[i][2])) return false;
        if (!ok(A[0][i], A[1][i], A[2][i])) return false;
    }
    return true;
}

void backtrack() {
    // save state
    int  backupA[3][3];
    bool backupX[3][3];
    memcpy(backupA, A, sizeof backupA);
    memcpy(backupX, isX, sizeof backupX);

    fillGrid();
    if (full() && valid()) {
        for (int i = 0; i < 3; ++i)
            cout << A[i][0] << " " << A[i][1] << " " << A[i][2] << "\n";
        exit(0);
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (isX[i][j]) {
                A[i][j] = 1;
                isX[i][j] = false;
                backtrack();
                // restore on failure
                memcpy(A,  backupA, sizeof backupA);
                memcpy(isX, backupX, sizeof backupX);
                return;
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            string s; 
            cin >> s;
            if (s == "X") {
                isX[i][j] = true;
            } else {
                isX[i][j] = false;
                A[i][j] = stoi(s);
            }
        }
    }

    backtrack();
    return 0;
}
