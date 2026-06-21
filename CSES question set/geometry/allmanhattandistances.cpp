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
typedef __int128 lll;

lll solve(vector<ll>& a) {
    sort(a.begin(), a.end());
    int n = a.size();
    lll s = 0;
    for (int k = 0; k < n; k++) s += (lll)a[k] * (2*k - n + 1);
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<ll> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];

    lll total = solve(x) + solve(y);

    string out;
    if (total == 0) out = "0";
    else { lll t = total; while (t > 0) { out += char('0' + (int)(t % 10)); t /= 10; } reverse(out.begin(), out.end()); }
    cout << out << '\n';
    return 0;
}