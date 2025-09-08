#include "combo.h"
#include <bits/stdc++.h>
using namespace std;

string guess_sequence(int N) {
    string ans;

    int t = press("AB");
    char first; string rest;
    if (t >= 1) {
        if (press("A") >= 1) { first = 'A'; rest = "BXY"; }
        else { first = 'B'; rest = "AXY"; }
    } else {
        if (press("X") >= 1) { first = 'X'; rest = "ABY"; }
        else { first = 'Y'; rest = "ABX"; }
    }
    ans += first;
    char B = rest[0], X = rest[1], Y = rest[2];

    while ((int)ans.size() < N - 1) {
        string q = ans + B + ans + X + B + ans + X + X + ans + X + Y;
        int r = press(q);
        if (r == (int)ans.size()) ans += Y;
        else if (r == (int)ans.size() + 1) ans += B;
        else ans += X;
    }

    if ((int)ans.size() < N) {
        if (press(ans + B) == (int)ans.size() + 1) ans += B;
        else if (press(ans + X) == (int)ans.size() + 1) ans += X;
        else ans += Y;
    }
    return ans;
}
