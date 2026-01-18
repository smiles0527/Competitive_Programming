#include <iostream>
#include <vector> 
using namespace std;

void insertSortInc(vector<int>& arr)
{
    for (int i = 1; i < arr.size(); i++)
    {
        int key = arr[i];
        int j = i-1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j]; 
            j--;
        }
        arr[j+1] = key;
    }
}

void insertSortDec(vector<int>& arr)
{
    for (int i = 1; i < arr.size(); i++)
    {
        int key = arr[i];
        int j = i-1;

        while (j >= 0 && arr[j] < key)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void printArray(const vector<int>& arr)
{
    for (int x : arr)
    {
        cout << x << " ";
    }
    cout << "\n";
}

int main()
{
    vector<int> arr = {2, 1, 3, 1, 29, 22, 30, 41, 32, 12, 11, 13};
    insertSortInc(arr);
    printArray(arr);
    insertSortDec(arr);
    printArray(arr);
}