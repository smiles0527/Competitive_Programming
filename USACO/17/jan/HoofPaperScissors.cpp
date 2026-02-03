#include <bits/stdc++.h>
using namespace std;

int main() {

    int n;
    cin >> n;

    vector<int> prefH(n + 1, 0), prefP(n + 1, 0), prefS(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        prefH[i] = prefH[i - 1];
        prefP[i] = prefP[i - 1];
        prefS[i] = prefS[i - 1];

        if (c == 'H') prefH[i]++;
        else if (c == 'P') prefP[i]++;
        else prefS[i]++;
    }

    auto best_wins = [&](int l, int r) {
        int cH = prefH[r] - prefH[l];
        int cP = prefP[r] - prefP[l];
        int cS = prefS[r] - prefS[l];
        return max({cS, cH, cP});
    };

    int ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = max(ans, best_wins(0, i) + best_wins(i, n));
    }

    cout << ans << "\n";
    return 0;
}
