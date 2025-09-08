#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<int> arr = {1, 2, 3, 4, 5};

    //PS array, no +1 implemenation
    //sum(l..r) = psa1[r]-psa1[l-1];
        //if l = 0, sum(l..r) = psa1[r]
    vector<int> psa1(arr.size());
    psa1[0] = arr[0];
    for(int i = 1; i < arr.size(); i++){
        psa1[i] = psa1[i-1] + arr[i];
    }
    

    //PS array, with +1 implementation
    //sum(l....r) = psa2[r+1]-psa2[l];
    vector<int> psa2(arr.size() + 1);
    psa2[0] = 0;
    for(int i = 1; i <= arr.size(); i++){
        psa2[i] = psa2[i-1] + arr[i-1];
    }
}