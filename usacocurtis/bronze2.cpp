#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; cin >> N;
    vector<int> a(N);
    vector<int> freq(N+1,0);
    for (int i = 0; i < N; i++){
        cin >> a[i];
        freq[a[i]]++;
    }
    int missing = 0;
    for (int i = 0; i <= N; i++){
        if(i > 0 && freq[i-1] == 0) missing++;
        int ans = max(freq[i], missing);
        cout << ans << "\n";
    }
    return 0;
}
