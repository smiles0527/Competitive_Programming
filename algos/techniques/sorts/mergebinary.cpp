/*
The mergesort routine is the top-down recursive merge sort. It splits the array into halves, recursively sorts each half, then merges them. That is the canonical 
𝑂(𝑛log⁡𝑛) divide-and-conquer version described in most algorithm texts.

The binarysearch routine is the iterative binary search. No recursion, simple while-loop, classic  O(logn) search on a sorted array.
*/

#include <bits/stdc++.h>
using namespace std;

bool binarysearch(vector<int> &arr, int x){
    int left = 0;
    int right = arr.size()-1;
    int mid = (right - left) / 2;

    while(left <= right){
        int mid = left + (right - left) / 2;
        if(x == arr[mid]){
            return true;
        } else if (x > arr[mid]){
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}


void merge(vector<int> &arr, int left, int mid, int right){

    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for(int i = 0; i < n1; i++){
        L[i] = arr[left + i];
    }
    for(int j = 0; j < n2; j++){
        R[j] = arr[mid + 1 + j];
    }
    int i = 0;
    int j = 0;;
    int k = left;

    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergesort(vector<int> &arr, int left, int right){

    if(left >= right){ 
        return;
    }

    int mid = left + (right - left) / 2;
    mergesort(arr, left, mid);
    mergesort(arr, mid + 1, right);
    merge(arr, left, mid, right);

}


int main(){
    vector<int> arr = {2, 1, 3, 1, 29, 22, 30, 41, 32, 12, 11, 13}; //41
    mergesort(arr, 0, arr.size()-1);
    if(binarysearch(arr, 123)){
        cout << "yes" << '\n';
    } else{
        cout << "no";
    }

    return 0;
}