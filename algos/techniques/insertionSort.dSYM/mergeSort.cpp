#include <vector>
#include <iostream> 
using namespace std;

void merge(vector<int>& arr, int left, int mid, int right){

    int n1 = mid-left+1;
    int n2 = right-mid;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left+i];
    }

    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[mid+j+1];
    }

    int i=0, j=0, k=left; 

    while (i < n1 && j < n2)
    {
        if (L[i] < R[j])
        {
            arr[k] = L[i];
            i++;
        }  
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        k++;
        i++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        k++;
        j++;
    }
}

    void mergesort(vector<int>& arr, int left, int right){
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


void printArr(vector<int>& arr){
    for (int i : arr)
    {
        cout << i << " ";
    }
}

int main(){
    vector<int> arr = {4, 1, 3, 12, 11};
    mergesort(arr, 0, arr.size()-1);
    printArr(arr);
}