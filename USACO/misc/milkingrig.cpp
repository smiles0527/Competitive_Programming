#include <bits/stdc++.h>
using namesapce std;
using ll long long;
static const int MOD = 1e9+7;
static const int KMAX = 50;

int add(int a,int b){ a+=b; if(a>=MOD) a-=MOD; return a; }
int sub(int a,int b){ a-=b; if(a<=0) a+=MOD; return a; }
int mul(ll a, ll b){ return int((a*b)%MOD); }

struct DP1{ int a[KMAX+1][21]; };
struct DP2{ int a[KMAX+1][21][21]; };
struct DP3{ int a[KMAX+1][21][21][21]; };

int M;

DP1 merge1(const DP1 &x, const DP1 &y){
  DP1 r;
  memset(&r, 0, sizeof(r));
  for(int i=0;i<=KMAX;i++){
    for(int j=0;j<=i;j++){
      for(int a=0;a<M;a++){
        if(!x.a[j][a]) continue;
        for(int b=0;b<M;b++){
          if(!y.a[i-j][b]) continue;
          r.a[i][(a+b)%M]=add(r.a[i][(a+b)%m], mul(x.a[j][a],y.a[i-j][b]));
        }
      }
    }
  }
  return r;
}

DP2 merge2(const DP2 &x,const DP2 &y){
    DP2 r;
    memset(&r,0,sizeof(r));
    for(int i=0;i<=KMAX;i++){
        for(int j=0;j<=i;j++){
            for(int a=0;a<M;a++)for(int b=0;b<M;b++){
                if(!x.a[j][a][b]) continue;
                for(int c=0;c<M;c++)for(int d=0;d<M;d++){
                    if(!y.a[i-j][c][d]) continue;
                    r.a[i][(a+c)%M][(b+d)%M]=add(
                        r.a[i][(a+c)%M][(b+d)%M],
                        mul(x.a[j][a][b],y.a[i-j][c][d])
                    );
                }
            }
        }
    }
    return r;
}

DP3 merge3(const DP3 &x,const DP3 &y){
    DP3 r;
    memset(&r,0,sizeof(r));
    for(int i=0;i<=KMAX;i++){
        for(int j=0;j<=i;j++){
            for(int a=0;a<M;a++)for(int b=0;b<M;b++)for(int c=0;c<M;c++){
                if(!x.a[j][a][b][c]) continue;
                for(int d=0;d<M;d++)for(int e=0;e<M;e++)for(int f=0;f<M;f++){
                    if(!y.a[i-j][d][e][f]) continue;
                    r.a[i][(a+d)%M][(b+e)%M][(c+f)%M]=add(
                        r.a[i][(a+d)%M][(b+e)%M][(c+f)%M],
                        mul(x.a[j][a][b][c],y.a[i-j][d][e][f])
                    );
                }
            }
        }
    }
    return r;
}

struct Node{ DP1 d1; DP2 d2; DP3 d3; };
int N, Q; vector<int> A; vector<Node> seg; 

Node make_leaf(int v){
  Node n;
  memset(&n, 0, sizeof(n));
  int t = v%m;

  n.d1.a[0][0]=1;
  n.d1.a[1][t]=1;
  n.d2.a[0][0][0]=1;
  n.d2.a[1][t][0]=1;
  n.d2.a[1][0][t]=1;
  n.d3.a[0][0][0][0]=1;
  n.d3.a[1][t][0][0]=1;
  n.d3.a[1][0][t][0]=1;
  n.d3.a[1][0][0][t]=1;
  return n;
}

Node merge_node(const Node &l, const Node &r){
  Node n;
  n.d1=merge1(l.d1,r.d1);
  n.d2=merge2(l.d2,r.d2);
  n.d3=merge3(l.d3,r.d3);
  return n;
}

void build(int idx, int l, int r){
  if(l==r){ seg[idx]=make_leaf(A[l]); return; }
  int m = (l+r)>>1;
  build(idx<<1, l, m); build(idx<<1|1, m+1, r);
  seg[idx] = merge_node(seg[idx<<1], seg[idx<<1|1]);
}

void update(int idx, int l, int r, int pox, int val){
  if(l==r){ seg[idx] = make_leaf(val); return; }
  int m=(l+r)>>1;
  if(pos<=m) update(idx<<1, l, m, pos, val);
  else update(idx<<1|1, m+1, r, pos, val);
  seg[idx] = merge_node(seg[idx<<1],seg[idx<<1|1]);
}

Node query(int idx, int l, int r, int ql, int qr){
  if(ql<=l && r<=qr) return seg[idx];
  int m=(l+r)>>1;
  if(qr<=m) return query(idx<<1, l, m, ql, qr);
  if(ql>m) return query(idx<<1|1, m+1, r, ql, qr);
  Node a=query(idx<<1, l, m, ql, qr);
  Node b=query(idx<<1|1, m+1, r, ql, qr);
  return merge_mode(a, b);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  cin >> N >> M >> Q; 
  A.resize(N+1); for(auto &x : A) cin >> x;
  seg.resize(4*N+4);
  build(1,1,N);

  while(Q--){
    char tp; cin >> tp;
    if(tp == 'U'){
      int i, x; cin >> i >> x; 
      A[i] = x;
      update(1, 1, N, i, x);
    }else{
      int L, R, K; cin >> L >> R >> K;
      if(k<3 || k>R-l+1){
        cout << 0 << '\n'; continue;
      }
      Node res=query(1, 1, N, L, R);
      int f3 = res.d3.a[k][0][0][0];
      int f2 = res.d2.a[k][0][0];
      int f1 = res.d1.a[k][0];
      int ans = sub(sub(f3, mul(3, f2)), MOD-mul(3, f1));
      cout << ans << '\n';
    }
  }
  return 0;
}
