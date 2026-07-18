#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int MOD = 1e9+7;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    cin >> a >> b;

    int inA[26] = {}, inB[26] = {};
    for (char c : a) inA[c - 'a'] = 1;
    for (char c : b) inB[c - 'a'] = 1;

    vector<char> x; char rep = 0;
    for (int i = 0; i < 26; i++) {
        if (inA[i] && !inB[i]) x.push_back('a' + i);
        else if (inB[i] && !inA[i]) rep = 'a' + i;
    }

    auto del = [](string s, char c) { string r; for (char ch : s) if (ch != c) r += ch; return r; };
    auto rpl = [](string s, char f, char t) { for (char& ch : s) if (ch == f) ch = t; return s; };

    char sil, q = '-';
    if (a.size() > b.size()) {
        if (rpl(b, rep, x[0]) == del(a, x[1])) { q = x[1]; sil = x[0]; }
        else { q = x[0]; sil = x[1]; }
    } else sil = x[0];

    cout << sil << ' ' << rep << '\n' << q << '\n';
    return 0;
}