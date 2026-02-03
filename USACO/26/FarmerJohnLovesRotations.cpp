#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    vector<int> val = a;
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    int num = val.size();

    int m = 3 * n;
    vector<int> b(m);
    for (int i = 0; i < m; i++){
        int x = a[i % n];
        int y = lower_bound(val.begin(), val.end(), x) - val.begin();
        b[i] = y;
    }

    long long inf = 4e18;

    vector<int> count(num, 0);
    vector<int> minr(2 * n);
    int h = 0;
    int r = -1;
    
    for (int l = 0; l < 2 * n; l++){
        while (r + 1 < m && r + 1 < l + n && h < num){
            r++;
            if (count[b[r]] == 0){
                h++;
            }
            count[b[r]]++;
        }
        minr[l] = r;
        if (l <= r){
            count[b[l]]--;
            if (count[b[l]] == 0){
                h--;
            }
        }
    }

    vector<vector<pair<long long, int>>> add1(2 * n), add2(2 * n);
    for (int l = 0; l < 2 * n; l++){
        int ri = minr[l];
        long long one = ri - 2LL * l;
        long long two = 2LL * ri - l;
        add1[l].push_back({one,ri});
        add2[l].push_back({two,ri});
    }

    vector<vector<int>> c2(2 * n);
    for (int l = 0; l < 2 * n; l++){
        int t = minr[l];
        if (t >= 0 && t < 2 * n){
            c2[t].push_back(l);
        }
    }
    priority_queue<int> maxL;

    vector<long long> ans(2 * n, inf);

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq1, pq2;

    for (int i = 0; i < 2 * n; i++){
        for (int j = 0; j < add1[i].size(); j++){
            pq1.push(add1[i][j]);
        }
        for (int j = 0; j < add2[i].size(); j++){
            pq2.push(add2[i][j]);
        }

        while(!pq1.empty() && pq1.top().second < i){
            pq1.pop();
        }

        while(!pq2.empty() && pq2.top().second < i){
            pq2.pop();
        }

        long long best = inf;

        for (int l : c2[i]){
            maxL.push(l);
        }

        int minL = i - n + 1;

        while (!maxL.empty() && maxL.top() < minL){
            maxL.pop();
        }
        if (!maxL.empty()){
            best = min(best, (long long)i - maxL.top());
        }

        if (!pq1.empty()){
            best = min(best, i + pq1.top().first);
        }

        if (!pq2.empty()){
            best = min(best, pq2.top().first - i);
        }

        ans[i] = best;
    }

    for (int i = 0; i < n; i++){
        long long best = min(ans[i], ans[i + n]);
        if (i) cout << ' ';
        cout << best;
    }
    return 0;
}
