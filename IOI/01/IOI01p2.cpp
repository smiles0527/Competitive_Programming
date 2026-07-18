#include <bits/stdc++.h>
using namespace std;

int p[7];
signed char memo[1 << 22];

int enc(const int* a){
    int e = 0;
    for (int i = 0; i < 7; i++) e |= a[i] << (3 * i);
    return e;
}

pair<int,int> sim(int* a, int s){
    int hand = a[s]; a[s] = 0;
    int gs = 0, go = 0, pos = s;
    while (hand > 0){
        pos = (pos + 1) % 7;
        if (hand > 1){
            if (a[pos] == 5){ gs++; a[pos]--; }
            else { a[pos]++; hand--; }
        } else {
            if (a[pos] >= 1 && a[pos] <= 4){ gs += a[pos] + 1; a[pos] = 0; }
            else go++;
            hand = 0;
        }
    }
    return {gs, go};
}

int V(int* a, int t){
    int key = (enc(a) << 1) | t;
    if (memo[key] != 127) return memo[key];
    bool emp = true;
    for (int i = 0; i < 7; i++) if (a[i]){ emp = false; break; }
    if (emp){ memo[key] = 0; return 0; }
    int best = t == 0 ? INT_MIN : INT_MAX;
    for (int s = 0; s < 7; s++) if (a[s] > 0){
        int b[7]; memcpy(b, a, sizeof b);
        auto g = sim(b, s);
        int d = t == 0 ? (g.first - g.second) : (g.second - g.first);
        int val = d + V(b, t ^ 1);
        if (t == 0) best = max(best, val); else best = min(best, val);
    }
    memo[key] = (signed char)best;
    return best;
}

bool empty7(const int* a){
    for (int i = 0; i < 7; i++) if (a[i]) return false;
    return true;
}

int main(){
    for (int i = 0; i < 7; i++) cin >> p[i];
    memset(memo, 127, sizeof memo);
    while (true){
        int best = INT_MIN, bs = -1;
        for (int s = 0; s < 7; s++) if (p[s] > 0){
            int b[7]; memcpy(b, p, sizeof b);
            auto g = sim(b, s);
            int val = (g.first - g.second) + V(b, 1);
            if (val > best){ best = val; bs = s; }
        }
        sim(p, bs);
        cout << bs + 1 << endl;
        if (empty7(p)) break;
        int mv;
        if (!(cin >> mv)) break;
        sim(p, mv - 1);
        if (empty7(p)) break;
    }
    return 0;
}