#include <iostream>
#include <vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int M, N, K;
    cin >> M >> N >> K;

    vector<bool> toggledRow(M+1);
    vector<bool> toggledCol(N+1);

    for(int i = 0; i < K; i++){
        char op;
        int x;
        cin >> op >> x;
        if(op == 'R') toggledRow[x] = !toggledRow[x];
        else           toggledCol[x] = !toggledCol[x];
    }

    long long rowsOdd = 0, colsOdd = 0;
    for(int i = 1; i <= M; i++) if(toggledRow[i]) rowsOdd++;
    for(int j = 1; j <= N; j++) if(toggledCol[j]) colsOdd++;

    long long gold = rowsOdd * (N - colsOdd) + (M - rowsOdd) * colsOdd;
    cout << gold << "\n";
    return 0;
}