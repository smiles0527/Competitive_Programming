#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int N;
        cin >> N;
        vector<int> a(N);
        for(int i = 0; i < N; i++){
            cin >> a[i];
        }

        
        vector<int> maxSuffix(N);
        maxSuffix[N-1] = a[N-1];
        for(int i = N - 2; i >= 0; i--){
            maxSuffix[i] = max(a[i], maxSuffix[i+1]);
        }

        
        for(int i = 0; i < N - 1; i++){
            if(maxSuffix[i+1] > a[i]){
                int L = maxSuffix[i+1]; 
                
                int p = -1;
                for(int j = N - 1; j > i; j--){
                    if(a[j] == L){
                        p = j;
                        break;
                    }
                }
                
                int val = a[p];
                for(int j = p; j > i; j--){
                    a[j] = a[j - 1];
                }
                a[i] = val;
                break; 
            }
        }

        
        
        
        
        vector<bool> keep(N, false);
        int mx = -1;
        for(int i = N - 1; i >= 0; i--){
            if(a[i] >= mx){
                keep[i] = true;
                mx = a[i];
            }
        }

        bool first = true;
        for(int i = 0; i < N; i++){
            if(keep[i]){
                if(!first) cout << " ";
                cout << a[i];
                first = false;
            }
        }
        cout << "\n";
    }

    return 0;
}
