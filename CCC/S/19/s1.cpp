#include <bits/stdc++.h>
using namespace std;

void hori(vector<vector<int>>& arr){
    swap(arr[0][0], arr[1][0]);
    swap(arr[0][1], arr[1][1]);
}

void vert(vector<vector<int>>& arr){
    swap(arr[0][0], arr[0][1]);
    swap(arr[1][0], arr[1][1]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<int>> arr = {
        {1,2},
        {3,4}
    };

    string str;
    getline(cin,str);

    int len = str.length();

    for (int i = 0; i < len; i++){
        if (str[i] == 'H'){
            hori(arr);
        }
        else if (str[i] == 'V'){
            vert(arr);
        }
    }

    for (int i = 0; i < arr.size(); i++){
        for (int j = 0; j < arr[i].size(); j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}