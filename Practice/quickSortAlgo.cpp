#include <bits/stdc++.h>
using namespace std;

int split(vector<int>& arr, int l, int h){
    int pivot = arr[h];
    int j = l;
    for (int i = l; i < h; i++){
        if (arr[i] < pivot){
            swap(arr[j], arr[i]);
        }
    }
    swap(arr[j], arr[h]);
    return j;
}


void quickSort(vector<int>& arr, int l, int h){
    if (l < h)
    {
        int part = split(arr, l, h);

        quickSort(arr, l, part-1);
        quickSort(arr, part+1, h);

    }
}

void printArray(vector<int>& arr){
    for (int i = 0; i < arr.size(); i++){
        cout << arr[i] << " ";
    }
}

int main(){
    vector<int> arr = {5,4,1,7,9,2,8};
    quickSort(arr, 0, arr.size()-1);
    printArray(arr);
}
