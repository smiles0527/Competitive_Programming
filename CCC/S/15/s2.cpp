#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int j, a;
    cin >> j >> a;
    vector<char> size(j);
    vector<bool> occ(j, false);
    for (int i = 0; i < j; i++){
        cin >> size[i];
    }

    vector<char> athe(a);
    vector<int> anum(a);
    
    int count = 0;

    for (int i = 0; i < a; i++){
        cin >> athe[i] >> anum[i];
    }
    for (int i = 0; i < a; i++){
        char asize = athe[i]; 
        int num = anum[i];

        if (asize == size[num-1] && !occ[num-1]){
            count++;
            occ[num-1] = true;
        }
    }

    for (int i = 0; i < a; i++){
        char asize = athe[i]; 
        int num = anum[i];

        if (asize > size[num-1] && !occ[num-1]){
            count++;
            occ[num-1] = true;
        }
    }

    cout << count;
}