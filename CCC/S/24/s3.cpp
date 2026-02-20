#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    
    vector<int> a(n);
    vector<int> b(b);

    for (int i = 0; i < n; i++){
        cin >> a[i];
    }  
    for (int i = 0; i < n; i++){
        cin >> b[i];
    }

    int count = 0;
    vector<char> direct;
    vector<vector<int>> runs;

    int l = 0;
    while (l < n){
        int r = l;
        while (r + 1 < n && b[r+1] == b[l]){
            r++;
        }
        runs.push_back({l,r});
        l = r+1;
    }

    vector<vector<int>> swipe;
    for (vector<int> run : runs){
        int start = run[0], end = run[1], v = b[start];
        if (start == end){
            if (a[start] != v){
                cout << "NO";
                return;
            }
        }
        else if (a[start] == v){
            swipe.push_back({start,end});
        }
        else if (a[end] == v){
            swipe.push_back({start,end});
            for (int i = start; i < end; i++){
                a[i] = v;
            }
        }
        else{
            cout << "NO";
            return;
        }
    }

    if (swipe.size() > k){
        cout << "NO";
        return;
    }
    for (int i = 0 ; )
}