#include <iostream>
#include <vector>
using namespace std;

void insertionSort(vector<int>& arr, int n){

    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i-1;

        while (j>=0 && key < arr[j])
        {
             arr[j+1] = arr[j];
             j--;
        }
        arr[j+1] = key;
    }
}

void printArray(vector<int>& arr)
{
    for (int i : arr)
    {
        cout << i << " ";
    }
}

int main(){
    vector<int> arr = {5, 11, 4, 7, 9};

    insertionSort(arr, 5);
    printArray(arr);

}