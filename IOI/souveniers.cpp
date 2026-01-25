#include <bits/stdc++.h>
#include "souvenirs.h"
using namespace std;

using ll = long long;
const int MM = 105;

static ll p[MM];
static int cntv[MM];
static int GN;
static ll GP0, LBOUND;

int fun(int last, ll w) {
    if (w < LBOUND) w = LBOUND;
    if (w >= GP0) w = GP0 - 1;
    auto [a, remain] = transaction(w);
    ll spent = w - remain;
    for (int x : a) cntv[x]++;

    while (!a.empty() && a.back() >= last) {
        spent -= p[a.back()];
        a.pop_back();
    }

    while (!a.empty() && a.front() + 1 < last) {
        ll k = (ll)a.size();
        ll w2 = spent ? (spent - 1) / k : LBOUND;
        if (w2 < LBOUND) w2 = LBOUND;
        if (w2 >= GP0) w2 = GP0 - 1;
        last = fun(last, w2);
        while (!a.empty() && a.back() >= last) {
            spent -= p[a.back()];
            a.pop_back();
        }
    }

    if (!a.empty()) {
        p[a.front()] = spent;
        return a.front();
    }
    return last;
}

void buy_souvenirs(int N, long long P0) {
    GN = N; GP0 = P0;
    LBOUND = max(1LL, GP0 - (GN - 1));
    memset(p, 0, sizeof(p));
    memset(cntv, 0, sizeof(cntv));

    fun(GN, GP0 - 1);

    for (int i = 1; i < N; i++) {
        while (cntv[i] < i) {
            transaction(p[i]);
            cntv[i]++;
        }
    }
}
