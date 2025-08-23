#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    int M;
    cin >> N >> M;
    vector<pair<ll,ll>> seg;
    seg.reserve(M);

    for(int i = 0; i < M; i++){
        ll r, c;
        cin >> r >> c;
        // height of triangle
        ll H = (N - r + 1);
        // this triangle contributes on [c, c+H) with line b - x
        seg.emplace_back(c, c + H);
    }

    sort(seg.begin(), seg.end(),
         [](auto &A, auto &B){ return A.first < B.first; });

    ll total = 0;
    // current right‐intercept = B, prev X where we last started summing
    ll B = 0, prevX = 0;
    bool first = true;

    for(auto &p: seg){
        ll c = p.first;
        ll b = p.second;
        if(first){
            // start the sweep
            B = b;
            prevX = c;
            first = false;
            continue;
        }
        // sum over x in [prevX, min(c, B) - 1]
        ll endX = min(c, B) - 1;
        if(prevX <= endX){
            ll cnt = endX - prevX + 1;
            // sum_{x=prevX..endX} (B - x)
            // = cnt*B - (prevX+endX)*cnt/2
            total += cnt * B 
                   - ((prevX + endX) * cnt) / 2;
        }
        // now bring in this new triangle
        B = max(B, b);
        prevX = c;
    }

    // final tail up to B-1
    if(!first){
        ll endX = B - 1;
        if(prevX <= endX){
            ll cnt = endX - prevX + 1;
            total += cnt * B 
                   - ((prevX + endX) * cnt) / 2;
        }
    }

    cout << total << "\n";
    return 0;
}
