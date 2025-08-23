#include <bits/stdc++.h>
using namespace std;

struct Cubie {
    array<int,8> cp;
    array<int,8> co;
    array<int,12> ep;
    array<int,12> eo;
};

static const int URF=0,UFL=1,ULB=2,UBR=3,DFR=4,DLF=5,DBL=6,DRB=7;
static const int UR=0,UF=1,UL=2,UB=3,DR=4,DF=5,DL=6,DB=7,FR=8,FL=9,BL=10,BR=11;
static const int U_=0,R_=1,F_=2,D_=3,L_=4,B_=5;

static Cubie mv[6];

static inline void rot4(int &a,int &b,int &c,int &d){int t=a;a=b;b=c;c=d;d=t;}

static Cubie id(){
    Cubie c;
    iota(c.cp.begin(),c.cp.end(),0);
    iota(c.ep.begin(),c.ep.end(),0);
    fill(c.co.begin(),c.co.end(),0);
    fill(c.eo.begin(),c.eo.end(),0);
    return c;
}

static void initMoves(){
    for(int f=0;f<6;f++) mv[f]=id();
    {
        auto &m=mv[U_];
        rot4(m.cp[URF],m.cp[UBR],m.cp[ULB],m.cp[UFL]);
        rot4(m.ep[UR],m.ep[UB],m.ep[UL],m.ep[UF]);
    }
    {
        auto &m=mv[R_];
        rot4(m.cp[URF],m.cp[DFR],m.cp[DRB],m.cp[UBR]);
        int x=m.co[URF];m.co[URF]=(x+2)%3; x=m.co[DFR];m.co[DFR]=(x+1)%3; x=m.co[DRB];m.co[DRB]=(x+2)%3; x=m.co[UBR];m.co[UBR]=(x+1)%3;
        rot4(m.ep[UR],m.ep[FR],m.ep[DR],m.ep[BR]);
    }
    {
        auto &m=mv[F_];
        rot4(m.cp[URF],m.cp[UFL],m.cp[DLF],m.cp[DFR]);
        int x=m.co[URF];m.co[URF]=(x+1)%3; x=m.co[UFL];m.co[UFL]=(x+2)%3; x=m.co[DLF];m.co[DLF]=(x+1)%3; x=m.co[DFR];m.co[DFR]=(x+2)%3;
        rot4(m.ep[UF],m.ep[FL],m.ep[DF],m.ep[FR]);
        m.eo[UF]^=1; m.eo[FL]^=1; m.eo[DF]^=1; m.eo[FR]^=1;
    }
    {
        auto &m=mv[D_];
        rot4(m.cp[DFR],m.cp[DLF],m.cp[DBL],m.cp[DRB]);
        rot4(m.ep[DF],m.ep[DL],m.ep[DB],m.ep[DR]);
    }
    {
        auto &m=mv[L_];
        rot4(m.cp[UFL],m.cp[ULB],m.cp[DBL],m.cp[DLF]);
        int x=m.co[UFL];m.co[UFL]=(x+1)%3; x=m.co[ULB];m.co[ULB]=(x+2)%3; x=m.co[DBL];m.co[DBL]=(x+1)%3; x=m.co[DLF];m.co[DLF]=(x+2)%3;
        rot4(m.ep[UL],m.ep[BL],m.ep[DL],m.ep[FL]);
    }
    {
        auto &m=mv[B_];
        rot4(m.cp[UBR],m.cp[DRB],m.cp[DBL],m.cp[ULB]);
        int x=m.co[UBR];m.co[UBR]=(x+1)%3; x=m.co[DRB];m.co[DRB]=(x+2)%3; x=m.co[DBL];m.co[DBL]=(x+1)%3; x=m.co[ULB];m.co[ULB]=(x+2)%3;
        rot4(m.ep[UB],m.ep[BR],m.ep[DB],m.ep[BL]);
        m.eo[UB]^=1; m.eo[BR]^=1; m.eo[DB]^=1; m.eo[BL]^=1;
    }
}

static Cubie mul(const Cubie&a,const Cubie&b){
    Cubie c;
    for(int i=0;i<8;i++){c.cp[i]=a.cp[b.cp[i]]; c.co[i]=(a.co[b.cp[i]]+b.co[i])%3;}
    for(int i=0;i<12;i++){c.ep[i]=a.ep[b.ep[i]]; c.eo[i]=(a.eo[b.ep[i]]^b.eo[i]);}
    return c;
}

static Cubie mpow(const Cubie&m,int p){
    if(p==1) return m;
    if(p==2) return mul(m,m);
    return mul(mul(m,m),m);
}

static int Cnk(int n,int k){ if(k<0||k>n) return 0; long long r=1; for(int i=1;i<=k;i++) r=r*(n+1-i)/i; return (int)r; }

static int getTwist(const Cubie&c){int r=0; for(int i=0;i<7;i++) r=3*r+c.co[i]; return r;}
static void setTwist(Cubie&c,int idx){int s=0; for(int i=6;i>=0;i--){c.co[i]=idx%3; s+=c.co[i]; idx/=3;} c.co[7]=(3-s%3)%3;}
static int getFlip(const Cubie&c){int r=0; for(int i=0;i<11;i++) r=(r<<1)|c.eo[i]; return r;}
static void setFlip(Cubie&c,int idx){int s=0; for(int i=10;i>=0;i--){c.eo[i]=idx&1; s^=c.eo[i]; idx>>=1;} c.eo[11]=s;

static int getSlice(const Cubie&c){int a=0,b=0; for(int i=0;i<12;i++) if(c.ep[i]>=8) a+=Cnk(i+1,++b); return a;}
static void setSlice(Cubie&c,int idx){
    vector<int> p(12,0); int b=4;
    for(int i=11;i>=0;i--) if(idx>=Cnk(i,b)){p[i]=1; idx-=Cnk(i,b); b--;}
    int e=8,f=0;
    for(int i=0;i<12;i++) c.ep[i]=p[i]?e++:f++;
}

static int permIndex(const vector<int>&a){
    int n=a.size(), r=0;
    for(int i=0;i<n;i++){ int s=0; for(int j=i+1;j<n;j++) if(a[j]<a[i]) s++; r=r*(n-i)+s; }
    return r;
}
static vector<int> permUnrank(int n,int idx){
    vector<int> a(n), v(n); iota(v.begin(),v.end(),0);
    for(int i=0;i<n;i++){ int q=idx%(n-i); idx/=(n-i); a[i]=v[q]; v.erase(v.begin()+q); }
    return a;
}

static int getCPerm(const Cubie&c){ vector<int> a(8); for(int i=0;i<8;i++) a[i]=c.cp[i]; return permIndex(a); }
static void setCPerm(Cubie&c,int idx){ vector<int> a=permUnrank(8,idx); for(int i=0;i<8;i++) c.cp[i]=a[i]; }

static int getMEPerm(const Cubie&c){
    int mapEdge[12]; for(int i=0;i<12;i++) mapEdge[i]=-1;
    mapEdge[FR]=0; mapEdge[FL]=1; mapEdge[BL]=2; mapEdge[BR]=3;3`
    int pos[4]={FR,FL,BL,BR}; vector<int> a(4);
    for(int i=0;i<4;i++) a[i]=mapEdge[c.ep[pos[i]]];
    return permIndex(a);
}
static void setMEPerm(Cubie&c,int idx){
    c=id();
    vector<int> a=permUnrank(4,idx);
    int pos[4]={FR,FL,BL,BR};
    int edges[4]={FR,FL,BL,BR};
    for(int i=0;i<4;i++) c.ep[pos[i]]=edges[a[i]];
}

static int getUDPerm(const Cubie&c){
    int mapEdge[12]; for(int i=0;i<12;i++) mapEdge[i]=-1;
    mapEdge[UR]=0; mapEdge[UF]=1; mapEdge[UL]=2; mapEdge[UB]=3;
    mapEdge[DR]=4; mapEdge[DF]=5; mapEdge[DL]=6; mapEdge[DB]=7;
    int pos[8]={UR,UF,UL,UB,DR,DF,DL,DB};
    vector<int> a(8);
    for(int i=0;i<8;i++) a[i]=mapEdge[c.ep[pos[i]]];
    return permIndex(a);
}
static void setUDPerm(Cubie&c,int idx){
    c=id();
    vector<int> a=permUnrank(8,idx);
    int pos[8]={UR,UF,UL,UB,DR,DF,DL,DB};
    int edges[8]={UR,UF,UL,UB,DR,DF,DL,DB};
    for(int i=0;i<8;i++) c.ep[pos[i]]=edges[a[i]];
}

static vector<array<int,18>> twistMove, flipMove, sliceMove;
static vector<array<int,18>> cpermMove, mepermMove, udpermMove;

static void buildMoveTables(){
    twistMove.assign(2187,{});
    flipMove.assign(2048,{});
    sliceMove.assign(495,{});
    cpermMove.assign(40320,{});
    mepermMove.assign(24,{});
    udpermMove.assign(40320,{});
    Cubie a,b;
    for(int i=0;i<2187;i++){
        a=id(); setTwist(a,i);
        for(int f=0;f<6;f++) for(int p=0;p<3;p++){ b=mul(a,mpow(mv[f],p+1)); twistMove[i][3*f+p]=getTwist(b); }
    }
    for(int i=0;i<2048;i++){
        a=id(); setFlip(a,i);
        for(int f=0;f<6;f++) for(int p=0;p<3;p++){ b=mul(a,mpow(mv[f],p+1)); flipMove[i][3*f+p]=getFlip(b); }
    }
    for(int i=0;i<495;i++){
        a=id(); setSlice(a,i);
        for(int f=0;f<6;f++) for(int p=0;p<3;p++){ b=mul(a,mpow(mv[f],p+1)); sliceMove[i][3*f+p]=getSlice(b); }
    }
    for(int i=0;i<40320;i++){
        a=id(); setCPerm(a,i);
        for(int f=0;f<6;f++) for(int p=0;p<3;p++){ b=mul(a,mpow(mv[f],p+1)); cpermMove[i][3*f+p]=getCPerm(b); }
    }
    for(int i=0;i<24;i++){
        a=id(); setMEPerm(a,i);
        for(int f=0;f<6;f++) for(int p=0;p<3;p++){ b=mul(a,mpow(mv[f],p+1)); mepermMove[i][3*f+p]=getMEPerm(b); }
    }
    for(int i=0;i<40320;i++){
        a=id(); setUDPerm(a,i);
        for(int f=0;f<6;f++) for(int p=0;p<3;p++){ b=mul(a,mpow(mv[f],p+1)); udpermMove[i][3*f+p]=getUDPerm(b); }
    }
}

static vector<int8_t> pr1_tw_slice, pr1_fl_slice;
static vector<int8_t> pr2_mc, pr2_mu;

static void bfsPruning(){
    pr1_tw_slice.assign(2187*495,-1);
    pr1_fl_slice.assign(2048*495,-1);
    deque<int> q;
    pr1_tw_slice[0]=0; q.push_back(0);
    while(!q.empty()){
        int x=q.front(); q.pop_front();
        int sl=x/2187, tw=x%2187, d=pr1_tw_slice[x];
        for(int m=0;m<18;m++){
            int nsl=sliceMove[sl][m], ntw=twistMove[tw][m];
            int y=nsl*2187+ntw;
            if(pr1_tw_slice[y]==-1){pr1_tw_slice[y]=d+1; q.push_back(y);}
        }
    }
    pr1_fl_slice[0]=0; q.clear(); q.push_back(0);
    while(!q.empty()){
        int x=q.front(); q.pop_front();
        int sl=x/2048, fl=x%2048, d=pr1_fl_slice[x];
        for(int m=0;m<18;m++){
            int nsl=sliceMove[sl][m], nfl=flipMove[fl][m];
            int y=nsl*2048+nfl;
            if(pr1_fl_slice[y]==-1){pr1_fl_slice[y]=d+1; q.push_back(y);}
        }
    }
    pr2_mc.assign(24*40320,-1);
    pr2_mu.assign(24*40320,-1);
    auto phase2Move=[&](int m){int f=m/3, p=m%3; return (f==U_||f==D_||p==1);};
    pr2_mc[0]=0; q.clear(); q.push_back(0);
    while(!q.empty()){
        int x=q.front(); q.pop_front();
        int me=x/40320, cp=x%40320, d=pr2_mc[x];
        for(int m=0;m<18;m++){
            if(!phase2Move(m)) continue;
            int nme=mepermMove[me][m];
            int ncp=cpermMove[cp][m];
            int y=nme*40320+ncp;
            if(pr2_mc[y]==-1){pr2_mc[y]=d+1; q.push_back(y);}
        }
    }
    pr2_mu[0]=0; q.clear(); q.push_back(0);
    while(!q.empty()){
        int x=q.front(); q.pop_front();
        int me=x/40320, up=x%40320, d=pr2_mu[x];
        for(int m=0;m<18;m++){
            if(!phase2Move(m)) continue;
            int nme=mepermMove[me][m];
            int nup=udpermMove[up][m];
            int y=nme*40320+nup;
            if(pr2_mu[y]==-1){pr2_mu[y]=d+1; q.push_back(y);}
        }
    }
}

static int ax[64], po[64];

static inline int h1(int sl,int tw,int fl){
    int a=pr1_tw_slice[sl*2187+tw];
    int b=pr1_fl_slice[sl*2048+fl];
    return max<int>(a,b);
}
static inline int h2(int me,int cp,int up){
    int a=pr2_mc[me*40320+cp];
    int b=pr2_mu[me*40320+up];
    return max<int>(a,b);
}

static bool ida1(int depth,int last,int sl,int tw,int fl){
    if(h1(sl,tw,fl)>depth) return false;
    if(depth==0) return sl==0&&tw==0&&fl==0;
    for(int m=0;m<18;m++){
        int f=m/3;
        if(f==last) continue;
        if(last!=-1 && ((last==U_&&f==D_)||(last==D_&&f==U_)||(last==R_&&f==L_)||(last==L_&&f==R_)||(last==F_&&f==B_)||(last==B_&&f==F_))) continue;
        int nsl=sliceMove[sl][m], ntw=twistMove[tw][m], nfl=flipMove[fl][m];
        ax[ax[0]+1]=f; po[ax[0]+1]=m%3; ax[0]++;
        if(ida1(depth-1,f,nsl,ntw,nfl)) return true;
        ax[0]--;
    }
    return false;
}

static bool ida2(int depth,int last,const Cubie&c0){
    if(depth<0) return false;
    int me=getMEPerm(c0), cp=getCPerm(c0), up=getUDPerm(c0);
    if(h2(me,cp,up)>depth) return false;
    if(depth==0) return me==0&&cp==0&&up==0;
    for(int m=0;m<18;m++){
        int f=m/3, p=m%3;
        if(!(f==U_||f==D_||p==1)) continue;
        if(f==last) continue;
        Cubie c1=mul(c0,mpow(mv[f],p+1));
        ax[ax[0]+1]=f; po[ax[0]+1]=p; ax[0]++;
        if(ida2(depth-1,f,c1)) return true;
        ax[0]--;
    }
    return false;
}

static string solve(const Cubie&scr){
    int sl=getSlice(scr), tw=getTwist(scr), fl=getFlip(scr);
    for(int d1=0; d1<=20; d1++){
        ax[0]=0;
        if(!ida1(d1,-1,sl,tw,fl)) continue;
        Cubie c=scr;
        for(int i=1;i<=ax[0];i++) c=mul(c, mpow(mv[ax[i]], po[i]+1));
        int save=ax[0];
        for(int d2=0; d2<=24; d2++){
            ax[0]=save;
            if(ida2(d2,-1,c)){
                static const char fc[6]={'U','R','F','D','L','B'};
                string out;
                for(int i=1;i<=ax[0];i++){
                    out.push_back(fc[ax[i]]);
                    if(po[i]==1) out.push_back('2');
                    else if(po[i]==2) out.push_back('\'');
                }
                return out;
            }
        }
    }
    return "";
}

static vector<int> facelets(54);

static Cubie faceletsToCubie(){
    int center[6]; for(int f=0;f<6;f++) center[f]=facelets[9*f+4];
    auto colorIdx=[&](int col){ for(int i=0;i<6;i++) if(center[i]==col) return i; return 0; };
    Cubie c=id();
    int cornerFacelet[8][3]={{8,9,20},{6,18,38},{0,36,47},{2,45,11},{29,26,15},{27,44,24},{33,53,42},{35,17,51}};
    int cornerColor[8][3]={{0,1,2},{0,2,4},{0,4,5},{0,5,1},{3,2,1},{3,4,2},{3,5,4},{3,1,5}};
    int edgeFacelet[12][2]={{5,10},{7,19},{3,37},{1,46},{32,14},{28,25},{30,41},{34,52},{23,12},{21,40},{50,39},{48,16}};
    int edgeColor[12][2]={{0,1},{0,2},{0,4},{0,5},{3,1},{3,2},{3,4},{3,5},{2,1},{2,4},{5,1},{5,4}};
    for(int i=0;i<8;i++){
        int a=colorIdx(facelets[cornerFacelet[i][0]]), b=colorIdx(facelets[cornerFacelet[i][1]]), d=colorIdx(facelets[cornerFacelet[i][2]]);
        for(int j=0;j<8;j++){
            for(int ori=0;ori<3;ori++){
                if(a==cornerColor[j][ori] && b==cornerColor[j][(ori+1)%3] && d==cornerColor[j][(ori+2)%3]){
                    c.cp[i]=j; c.co[i]=ori%3; j=8; break;
                }
            }
        }
    }
    for(int i=0;i<12;i++){
        int a=colorIdx(facelets[edgeFacelet[i][0]]), b=colorIdx(facelets[edgeFacelet[i][1]]);
        for(int j=0;j<12;j++){
            if(a==edgeColor[j][0] && b==edgeColor[j][1]){ c.ep[i]=j; c.eo[i]=0; break; }
            if(a==edgeColor[j][1] && b==edgeColor[j][0]){ c.ep[i]=j; c.eo[i]=1; break; }
        }
    }
    return c;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    initMoves();
    buildMoveTables();
    bfsPruning();

    vector<string> tok;
    string t;
    while(tok.size()<54 && (cin>>t)) tok.push_back(t);
    if(tok.size()<54) return 0;

    vector<string> U(9),L(9),F(9),R(9),B(9),D(9);
    for(int i=0;i<9;i++) U[i]=tok[i];
    for(int r=0;r<3;r++){
        for(int c=0;c<3;c++) L[r*3+c]=tok[9 + r*12 + c];
        for(int c=0;c<3;c++) F[r*3+c]=tok[9 + r*12 + 3 + c];
        for(int c=0;c<3;c++) R[r*3+c]=tok[9 + r*12 + 6 + c];
        for(int c=0;c<3;c++) B[r*3+c]=tok[9 + r*12 + 9 + c];
    }
    for(int i=0;i<9;i++) D[i]=tok[45+i];

    vector<string> centers={U[4],R[4],F[4],D[4],L[4],B[4]};
    auto mapC=[&](const string& s){ for(int i=0;i<6;i++) if(centers[i]==s) return i; return 0; };

    auto put=[&](int f,const vector<string>&src){ for(int i=0;i<9;i++) facelets[f*9+i]=mapC(src[i]); };
    put(0,U);
    put(1,R);
    put(2,F);
    put(3,D);
    put(4,L);
    put(5,B);

    Cubie c=faceletsToCubie();
    string ans=solve(c);
    cout<<ans<<"\n";
    return 0;
}

