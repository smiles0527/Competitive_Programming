#include <bits/stdc++.h>
using namespace std;

int partition(vector<int>& arr, int l, int r)
{
    int i = l-1; int pivot = arr[r];
    for (int j = l; j <= r-1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i], arr[r]);
    return i+1; 
}

void quickSort(vector<int>& arr, int l, int r)
{
    if (l < r)
    {
        int pivot = partition(arr, l, r);
        quickSort(arr, l, pivot-1);
        quickSort(arr, pivot+1, r);
    }
} 

int main()
{
    vector<int> arr = {4,3,1,9,7,10,6,5};
    quickSort(arr, 0, arr.size()-1);
    for (int i : arr)
    {
        cout << i << " ";
    }
}