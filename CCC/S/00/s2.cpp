#include <bits/stdc++.h>
using namespace std;

int main(){
    int num;
    cin >> num;
    vector<int> stream(num);
    for (int i = 0; i < num; i++){
        cin >> stream[i];
    }
    while (true){
        int c;
        cin >> c;
        if (c == 99){
            int n, p;
            cin >> n >> p;
            int cur = stream[n];
            stream[n] = cur * (p / 100);
            stream.insert(stream.begin() + n, cur * ((100-p)/100));
        }
        else if (c == 88){
            int n;
            cin >> n;

            vector<int> result;
            int i = 0;
            while (i < n){
                result.push_back(stream[i]);
                i++;
            }
            result.push_back(stream[n] + stream[n+1]);
            i+=2;
            while (i < stream.size()){
                result.push_back(stream[i]);
                i++;
            }
            stream = result;
        }
        else{
            break;
        }
    }
    for (int i : stream){
        cout << stream[i] << " ";
    }

}