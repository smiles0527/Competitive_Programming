#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<char> days(N);
    for (int i = 0; i < N; i++){
        cin >> days[i];
    }
    vector<int> left(N, 0), right(N, 0);
    left[0] = (days[0] == 'S' ? 1 : 0);
    for (int i = 1; i < N; i++){
        left[i] = (days[i] == 'S' ? left[i - 1] + 1 : 0);
    }
    right[N - 1] = (days[N - 1] == 'S' ? 1 : 0);
    for (int i = N - 2; i >= 0; i--){
        right[i] = (days[i] == 'S' ? right[i + 1] + 1 : 0);
    }
    int ans = 0;
    bool hasP = false;
    for (int i = 0; i < N; i++){
        if (days[i] == 'P'){
            hasP = true;
            int leftCount = (i > 0 ? left[i - 1] : 0);
            int rightCount = (i < N - 1 ? right[i + 1] : 0);
            ans = max(ans, leftCount + 1 + rightCount);
        }
    }
    if (!hasP) ans = N - 1;
    cout << ans << "\n";
    return 0;
}
