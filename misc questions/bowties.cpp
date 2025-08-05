#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct P { int x, y, idx; };

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<P> pts(N);
    for(int i = 0; i < N; i++){
        cin >> pts[i].x >> pts[i].y;
        pts[i].idx = i;
    }

    vector<int> U(N), D(N), L(N), R(N);

    sort(pts.begin(), pts.end(), [](const P &a, const P &b){
        if(a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    for(int i = 0; i < N;){
        int j = i;
        while(j < N && pts[j].x == pts[i].x) j++;
        int len = j - i;
        for(int k = 0; k < len; k++){
            D[pts[i+k].idx] = k;
            U[pts[i+k].idx] = len - 1 - k;
        }
        i = j;
    }

    sort(pts.begin(), pts.end(), [](const P &a, const P &b){
        if(a.y != b.y) return a.y < b.y;
        return a.x < b.x;
    });
    for(int i = 0; i < N;){
        int j = i;
        while(j < N && pts[j].y == pts[i].y) j++;
        int len = j - i;
        for(int k = 0; k < len; k++){
            L[pts[i+k].idx] = k;
            R[pts[i+k].idx] = len - 1 - k;
        }
        i = j;
    }

    ll ans = 0;
    for(int i = 0; i < N; i++){
        ans += ll(U[i])*R[i] * (ll(D[i])*L[i])
             + ll(U[i])*L[i] * (ll(D[i])*R[i]);
    }

    cout << ans << "\n";
    return 0;
}
