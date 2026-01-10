#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, B;
    cin >> n >> B;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    int pos = 0;
    for(int i = 0; i < n; i++) if(a[i] == B) { pos = i; break; }

    // counts of left balances
    vector<long long> cnt(2*n+5, 0);
    int offset = n + 2;
    int bal = 0;
    cnt[offset] = 1; // empty left

    // build left of B
    for(int i = pos-1; i >= 0; i--){
        if(a[i] > B) bal++;
        else if(a[i] < B) bal--;
        cnt[bal + offset]++;
    }

    long long ans = 0;
    int rbal = 0;
    // iterate suffixes including B
    for(int j = pos; j < n; j++){
        if(a[j] > B) rbal++;
        else if(a[j] < B) rbal--;
        // we need left_bal + rbal == 0
        ans += cnt[-rbal + offset];
    }

    cout << ans << "\n";
    return 0;
}