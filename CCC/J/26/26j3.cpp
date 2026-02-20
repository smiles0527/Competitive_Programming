#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string a, b; cin >> a >> b;
    ll ea = 0, eb = 0;
    int i = 0, j = 0;

    while(i < (int)a.size() && j < (int)b.size()){
        if(a[i] == b[j]){
            ea += 1;
            eb += 1;
            i++;
            j++;
        }else if(
            (a[i] == 'R' && b[j] == 'G') ||
            (a[i] == 'G' && b[j] == 'B') ||
            (a[i] == 'B' && b[j] == 'R') 
        ){
            ea += 1;
            j++;
        }else{
            eb += 1;
            i++;
        }
    }
    ea += a.size() - i;
    eb += b.size() - j;
    cout << ea << ' ' << eb << '\n';
}