#include <bits/stdc++.h>
using namespace std;

int main() {
    int num;
    cin >> num;
    vector<double> stream(num);
    for (int i = 0; i < num; i++){
        cin >> stream[i];
    }

    while (true) {
        int c;
        cin >> c;

        if (c == 99){
            int n, p;
            cin >> n >> p;
            n--;

            double cur = stream[n];
            double left  = cur * (p / 100.0);
            double right = cur - left;

            stream[n] = right;
            stream.insert(stream.begin() + n, left);
        } 
        else if (c == 88){
            int n;
            cin >> n;
            n--;

            vector<double> result;
            for (int i = 0; i < n; i++) result.push_back(stream[i]);
            result.push_back(stream[n] + stream[n + 1]);
            for (int i = n + 2; i < (int)stream.size(); i++) result.push_back(stream[i]);

            stream = result;
        } 
        else{
            break;
        }
    }

    for (int i = 0; i < (int)stream.size(); i++){
        cout << (long long)llround(stream[i]) << " ";
    }
}
