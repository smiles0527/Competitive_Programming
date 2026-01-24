#include <bits/stdc++.h>
using namespace std;
 
const long long MOD = 1000000007;
 
long long modexp(long long base, __int128 exp, long long mod) {
    long long res = 1;
    base %= mod;
    while(exp > 0) {
        if(exp & 1)
            res = ( (__int128)res * base ) % mod;
        base = ( (__int128)base * base ) % mod;
        exp /= 2;
    }
    return res;
}
 
long long modinv(long long x, long long mod) {
    return modexp(x, mod - 2, mod);
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long K, L;
    int N;
    cin >> K >> N >> L;
    string T;
    cin >> T;
    
    long long countM = 0;
    for(char c : T)
        if(c == 'M')
            countM++;
    
    long long prod = 1;
    long long state = 0;
    for(char c : T){
        if(c == 'M'){
            state += K;
        } else { // 'O'
            prod = (prod * (state % MOD)) % MOD;
            state -= 1;
        }
    }
    
    long long factK = 1;
    for (int i = 1; i <= K; i++)
        factK = (factK * i) % MOD;
    
    __int128 expFact = (__int128)L * countM;
    long long denom = modexp(factK, expFact, MOD);
    long long num = modexp(prod, L, MOD);
    long long ans = (num * modinv(denom, MOD)) % MOD;
    
    cout << ans;
    return 0;
}
