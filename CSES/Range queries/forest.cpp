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
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

int n, q;
int p[1001][1001];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    for (int i = 1; i <= n; i++){
        string row; cin >> row;
        for (int j = 1; j <= n; j++){
            int a = (row[j-1] == '*');
            p[i][j] = a + p[i-1][j] + p[i][j-1] - p[i-1][j-1];
        }
    }

    while (q--){
        int y1, x1, y2, x2; cin >> y1 >> x1 >> y2 >> x2;
        cout << p[y2][x2] - p[y1-1][x2] - p[y2][x1-1] + p[y1-1][x1-1] << '\n';
    }
    return 0;
}