#include <bits/stdc++.h>
using namespace std;

struct Op{ int tp,x,p,q,y,k; };

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while(T--){
        int N,M; cin >> N >> M;
        string t; cin >> t;
        vector<string> s(N);
        for(int i=0;i<N;i++) cin >> s[i];

        vector<Op> ops;

        auto enc = [&](int x,int p){ return x*M + p; };
        auto decx = [&](int v){ return v / M; };
        auto decp = [&](int v){ return v % M; };

        vector<vector<int>> pos(26);
        pos.assign(26, {});
        for(int x=0;x<N;x++) for(int p=0;p<M;p++) pos[s[x][p]-'a'].push_back(enc(x,p));

        auto pushcell = [&](int x,int p){ pos[s[x][p]-'a'].push_back(enc(x,p)); };

        auto sw1 = [&](int x,int p,int q){
            if(p==q) return;
            swap(s[x][p], s[x][q]);
            pushcell(x,p); pushcell(x,q);
        };
        auto sw2 = [&](int x,int y,int k){
            if(x==y) return;
            swap(s[x][k], s[y][k]);
            pushcell(x,k); pushcell(y,k);
        };

        auto getloc = [&](int c,int i)->int{
            auto &v = pos[c];
            while(!v.empty()){
                int z = v.back();
                int x = decx(z), p = decp(z);
                if(s[x][p]-'a' != c){ v.pop_back(); continue; }
                if(x==0 && p>i){ v.pop_back(); continue; }
                return z;
            }
            return -1;
        };

        /* lock suffix: only touch indices <= i in s1, so go i=M-1..0 */
        for(int i=M-1;i>=0;i--){
            if(s[0][i]==t[i]) continue;
            int c = t[i]-'a';

            int z = getloc(c,i);

            int x = decx(z), p = decp(z);

            /* want c to land at (x,i), then if x!=0 do column swap into s1 */
            if(p!=i){
                sw1(x,p,i);
                ops.push_back({1,x+1,p+1,i+1,0,0});
            }
            if(x!=0){
                sw2(0,x,i);
                ops.push_back({2,1,0,0,x+1,i+1});
            }
        }

        cout << ops.size() << "\n";
        for(auto &o: ops){
            if(o.tp==1) cout << "1 " << o.x << " " << o.p << " " << o.q << "\n";
            else cout << "2 " << o.x << " " << o.y << " " << o.k << "\n";
        }
    }
    return 0;
}