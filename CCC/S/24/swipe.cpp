#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arrA(n), arrB(n);
    for(int i = 0; i < n; i++) cin >> arrA[i];
    for(int i = 0; i < n; i++) cin >> arrB[i];
s
    vector<int> valTrack;
    vector<pair<int,int>> rangeTrack;
    int l = 0, r = 0, val = arrB[0];
    valTrack.push_back(val);
    for(int i = 1; i < n; i++){
        if(arrB[i] == val){
            r++;
        } else {
            rangeTrack.emplace_back(l, r);
            l = r = i;
            val = arrB[i];
            valTrack.push_back(val);
        }
    }
    rangeTrack.emplace_back(l, r);

    int cur = 0;
    vector<pair<int,int>> swipeL, swipeR;
    for(int i = 0; i < n && cur < (int)valTrack.size(); i++){
        if(arrA[i] == valTrack[cur]){
            int left = rangeTrack[cur].first;
            int right = rangeTrack[cur].second;
            if(left < i)  swipeL.emplace_back(left, i);
            if(right > i) swipeR.emplace_back(i, right);
            cur++;
        }
    }

    if(cur == (int)valTrack.size()){
        cout << "YES\n";
        int k = swipeL.size() + swipeR.size();
        cout << k << "\n";
        for(auto &p : swipeL)
            cout << "L " << p.first << " " << p.second << "\n";
        for(int i = (int)swipeR.size() - 1; i >= 0; i--)
            cout << "R " << swipeR[i].first << " " << swipeR[i].second << "\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}