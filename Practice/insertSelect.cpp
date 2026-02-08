#include <bits/stdc++.h>
using namespace std;

void insertSort(vector<int>& arr, int n){
    for (int i = 1; i < n; i++){
        int key = arr[i];
        int j = i-1;

        while (j >= 0 && arr[j] > key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void selectSort(vector<int>& arr, int n){
    for (int i = 0; i < n - 1; i++){
        int min = i;
        for (int j = i+1; j < n; j++){
            if (arr[j] < arr[min]){
                min = j;
            }
        }

        swap(arr[i], arr[min]);
    }
}

void printArr(vector<int>& arr, int n){
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
}

int main(){
    vector<int> arr1 = {3, 9, 16, 4, 11};
    vector<int> arr2 = {2, 4, 1, 3, 5};
    
    insertSort(arr1, arr1.size());
    selectSort(arr2, arr2.size());

    printArr(arr1, arr1.size());
    printArr(arr2, arr2.size());
}