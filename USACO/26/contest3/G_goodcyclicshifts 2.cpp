#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 200005;
int p[MAXN];
ll bit[MAXN];
ll Ng;
ll ckD[MAXN + 2], ccD[MAXN + 2];
int goods[MAXN];

void upd(int i){ for(; i<=Ng; i+=i&-i) bit[i]++; }
ll qry(int i){ ll s=0; for(; i>0; i-=i&-i) s+=bit[i]; return s; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; if(!(cin>>T)) return 0;
    while(T--){
        int N; cin >> N; Ng = N;
        for(int i=1;i<=N;i++) cin>>p[i];

        for(int i=1;i<=N;i++) bit[i]=0;
        ll inv0 = 0;
        for(int i=N;i>=1;i--){ inv0+=qry(p[i]-1); upd(p[i]); }

        for(int k=0;k<=N;k++){ ckD[k]=0; ccD[k]=0; }
        
        // |k=a| over l,r

        auto addAbs = [&](int l, int r, ll a){
            if(l > r) return;
            int hi1 = (int) min<ll>(r, a - 1);

            if(l <= hi1){
                ckD[l] -= 1;
                ckD[hi1+1] += 1;
                ccD[l] += a;
                ccD[hi1 + 1] -= a;
            }

            int lo2 = (int)max<ll>(l, a);

            if(lo2 <= r){
                ckD[lo2] += 1;
                ckD[r + 1] -= 1;
                ccD[lo2] -= a;
                ccD[r+1] += a;
            }
        };

        for(int i = 1; i <= N; i++){
            ll v = p[i];
            addAbs(0, i-1, (ll)i-v); // before wrap
            addAbs(i, N-1, (ll)N + i - v); // after wrap
        }

        ll Ik = inv0, ckP = 0, ccP = 0; int gc = 0;
        for(int k = 0; k < N; k++){
            ckP += ckD[k]; ccP += ccD[k];
            ll disp = ckP*(ll) k + ccP; //D_K
            if(2*Ik <= disp) goods[gc++] = (N-k)%N; // left k -> right s
            Ik += (ll)N + 1 - 2LL*p[k+1]; // I_{K+1}
        }

        sort(goods, goods+gc);
        cout << gc << '\n';
        for(int i = 0; i < gc; i++){
            cout << goods[i];
            if(i + 1 < gc) cout << ' ';
        }
        cout << '\n';
    }
    return 0;
}