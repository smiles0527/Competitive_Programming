#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<int>& arr;
    int target;

    //brute force technique o(n^2) & o(1)
    for(int i = 0; i < arr.size(); i++){
        for(int j = i + 1; j < arr.size(); j++){
            if(arr[i] + arr[j] == target) return true;
        }
    }

    //two-poiner technique o(n) & o(1)
    int left = 0; int right = arr.size()-1;
    while(left < right){
        int sum = arr[left] + arr[right];
        if(sum == target) return true;
        else if(sum < target) left++;
        else right++;
    }
    
}