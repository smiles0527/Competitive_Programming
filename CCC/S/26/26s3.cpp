#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n;
    vector<long long> c(n+1);
    bool unk = true;
    for(int i=1;i<=n;i++){
        cin >> c[i];
        if(c[i]!=-1) unk = false;
    }

    if(unk){
        int k = 100;
        cout << k << "\n";
        int cur = 1;

        /* no values, so just shotgun disjoint partitions
           hope: huge N => tons of winning partitions; 100 tries usually hits
           keep disjoint: 6 indices per guess (3+3) */
        for(int t=0;t<k;t++){
            int a = 3, b = 3;
            cout << a << " " << b << "\n";
            cout << cur << " " << cur+1 << " " << cur+2 << "\n";
            cout << cur+3 << " " << cur+4 << " " << cur+5 << "\n";
            cur += 6;
        }
        return 0;
    }

    vector<int> ev, od;
    for(int i=1;i<=n;i++){
        if((c[i]&1LL)==0) ev.push_back(i);
        else od.push_back(i);
    }

    auto out = [&](vector<int> A, vector<int> B){
        cout << "YES\n";
        cout << (int)A.size() << " " << (int)B.size() << "\n";
        for(int i=0;i<(int)A.size();i++){
            if(i) cout << " ";
            cout << A[i];
        }
        cout << "\n";
        for(int i=0;i<(int)B.size();i++){
            if(i) cout << " ";
            cout << B[i];
        }
        cout << "\n";
    };

    if(n >= 4){
        /* aim for d=2:
           need both sums even -> easiest constructions by parity */
        if((int)ev.size() >= 2){
            out({ev[0]}, {ev[1]});
            return 0;
        }
        if((int)ev.size() == 1){
            out({ev[0]}, {od[0], od[1]});
            return 0;
        }
        out({od[0], od[1]}, {od[2], od[3]});
        return 0;
    }

    if(n == 2){
        if(std::gcd(c[1], c[2]) > 1) out({1}, {2});
        else cout << "NO\n";
        return 0;
    }

    /* n==3
       try parity d=2 first; if all odd, brute the finite partition options */
    if((int)ev.size() >= 2){
        out({ev[0]}, {ev[1]});
        return 0;
    }
    if((int)ev.size() == 1){
        out({ev[0]}, {od[0], od[1]});
        return 0;
    }

    long long a=c[1], b=c[2], d=c[3];

    if(std::gcd(a,b) > 1){ out({1},{2}); return 0; }
    if(std::gcd(a,d) > 1){ out({1},{3}); return 0; }
    if(std::gcd(b,d) > 1){ out({2},{3}); return 0; }

    if(std::gcd(a, b+d) > 1){ out({1},{2,3}); return 0; }
    if(std::gcd(b, a+d) > 1){ out({2},{1,3}); return 0; }
    if(std::gcd(d, a+b) > 1){ out({3},{1,2}); return 0; }

    cout << "NO\n";
    return 0;
}