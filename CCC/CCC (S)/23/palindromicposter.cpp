#include <bits/stdc++.h>
using namespace std;
vector<vector<char>> poster; //Our poster, will resize later
vector<char> alphabet {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

void printPoster(int N, int M){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cout << poster[i][j];
        }
        cout << '\n';
    }
}
void printPosterRotated(int N, int M){
    for (int i = N - 1; i >= 0; i--){
        for (int j = 0; j < M; j++){
            cout << poster[j][i];
        }
        cout << '\n';
    }
}
int main(){
    int N, M, R, C;
    cin >> N >> M >> R >> C;
    if (R == N && C == M || (R != N && R != 0 && C != M && C != 0)){
        poster.resize(N, vector<char> (M, 'a'));
        for (int i = 0; i < R; i++){
            for (int j = 0; j < M; j++){
                poster[i][j] = 'b';    
            }
        }
        for (int i = R; i < N; i++){
            for (int j = 0; j < C; j++){
                poster[i][j] = 'b';
            }
        }
    }
    else if (R == 0 && C == 0){
        poster.resize(N, vector<char> (M, 'a'));
        int letter = 0;
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M; j++){
                poster[i][j] = alphabet[letter];
                letter++;
                letter %= 26;
            }
            letter += (i + 1) * 3;
            letter %= 26;
        }
    }
    else if (R == 0){
        poster.resize(N, vector<char> (M, 'a'));
        for (int i = 0; i < N; i++){
            poster[i][M - 1] = 'b';
        }
        for (int j = C; j < M; j++){
            poster[N - 1][j] = alphabet[(poster[N - 1][j] - 'a' + 1)];
        }
    }
    else if (R == N){
        poster.resize(N, vector<char> (M, 'a'));
        if (M % 2 == C % 2){
            int goodCols = M;
            int front = 0, back = M - 1;
            while (goodCols > C){
                poster[0][front] = 'b';
                poster[0][back] = 'b';
                front++; back--;
                goodCols -= 2;
            }
        }
        else if (M % 2 == 1){
            int goodCols = M;
            int front = 0, back = M - 1;
            while (goodCols > C + 1){
                poster[0][front] = 'b';
                poster[0][back] = 'b';
                front++; back--;
                goodCols -= 2;
            }
            //Just change the middle to subtract one more palindromic column
            int mid = (front + back) / 2;
            poster[0][mid] = 'b';
            
        }
        //Otherwise impossible
        else{
            cout << "IMPOSSIBLE";
            return 0;
        }
    }
    //No palindromic columns
    else if (C == 0){
        poster.resize(M, vector<char> (N, 'a')); //Resize oppositely
        //Same logic, just swapping N and M
        for (int i = 0; i < M; i++) poster[i][N - 1] = 'b';
        for (int j = R; j <= N; j++)  poster[M - 1][j] = alphabet[poster[M - 1][j] - 'a' + 1];
        printPosterRotated(N, M);
        return 0;  
    }
    else if (C == M){
        poster.resize(M, vector<char> (N, 'a'));
        if (N % 2 == R % 2){
            int goodCols = N;
            int front = 0, back = N - 1;
            while (goodCols > R){
                poster[0][front] = 'b';
                poster[0][back] = 'b';
                front++; back--;
                goodCols -= 2;
                
            }
            printPosterRotated(N, M);
            return 0;
        }
        else if(N % 2 == 1){
            int goodCols = N;
            int front = 0, back = N - 1;
            while (goodCols > R + 1){
                poster[0][front] = 'b';
                poster[0][back] = 'b';
                front++; back--;
                goodCols -= 2;
                
            }
            int mid = (front + back) / 2;
            poster[0][mid] = 'b';
            
            printPosterRotated(N, M);
            return 0;
            
        }
        else{
            cout << "IMPOSSIBLE";
            return 0;
        }
        
    }
    printPoster(N, M);
    return 0;
    
}

