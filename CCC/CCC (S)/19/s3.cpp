#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A[3][3];
    bool isX[3][3];
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            string s; 
            cin >> s;
            if(s=="X"){ isX[i][j]=true; }
            else{ isX[i][j]=false; A[i][j]=stoi(s); }
        }
    }

    auto fillRow = [&](int i){
        int cnt=0, xj=-1;
        for(int j=0; j<3; j++) if(isX[i][j]){ cnt++; xj=j; }
        if(cnt==1){
            int a, b;
            if(xj==0){ a=A[i][1]; b=A[i][2]; A[i][0]=2*a - b; }
            if(xj==1){ a=A[i][0]; b=A[i][2]; A[i][1]=(a + b)/2; }
            if(xj==2){ a=A[i][0]; b=A[i][1]; A[i][2]=2*b - a; }
            isX[i][xj]=false;
        } else if(cnt==3){
            A[i][0]=A[i][1]=A[i][2]=0;
            isX[i][0]=isX[i][1]=isX[i][2]=false;
        }
    };

    auto fillCol = [&](int j){
        int cnt=0, xi=-1;
        for(int i=0; i<3; i++) if(isX[i][j]){ cnt++; xi=i; }
        if(cnt==1){
            int a, b;
            if(xi==0){ a=A[1][j]; b=A[2][j]; A[0][j]=2*a - b; }
            if(xi==1){ a=A[0][j]; b=A[2][j]; A[1][j]=(a + b)/2; }
            if(xi==2){ a=A[0][j]; b=A[1][j]; A[2][j]=2*b - a; }
            isX[xi][j]=false;
        } else if(cnt==3){
            A[0][j]=A[1][j]=A[2][j]=0;
            isX[0][j]=isX[1][j]=isX[2][j]=false;
        }
    };

    while(true){
        bool anyX=false;
        for(int i=0;i<3;i++)for(int j=0;j<3;j++)if(isX[i][j]) anyX=true;
        if(!anyX) break;
        for(int i=0;i<3;i++) fillRow(i);
        for(int j=0;j<3;j++) fillCol(j);
    }

    for(int i=0; i<3; i++){
        cout << A[i][0] << " " << A[i][1] << " " << A[i][2] << "\n";
    }
    return 0;
}
