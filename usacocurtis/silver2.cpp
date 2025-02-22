#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 1000005;
const int LOGN = 21;
const int BUFSZ = 1 << 20;


char ibuf[BUFSZ];
int ipos = 0, ilen = 0;
inline int getChar(){
    if(ipos == ilen){
        ilen = (int)fread(ibuf, 1, BUFSZ, stdin);
        if(!ilen) return EOF;
        ipos = 0;
    }
    return ibuf[ipos++];
}
inline int readInt(){
    int c = getChar();
    while(c != EOF && ((c < '0' && c != '-') || c > '9'))
        c = getChar();
    if(c == EOF) return 0;
    bool neg = (c == '-');
    if(neg) c = getChar();
    int x = 0;
    while(c != EOF && c >= '0' && c <= '9'){
        x = x * 10 + (c - '0');
        c = getChar();
    }
    return neg ? -x : x;
}


int par[MAXN], depth[MAXN], tin[MAXN], tout[MAXN];
int up[LOGN][MAXN];
int fenw[MAXN];       
int childIdx[MAXN];   
int dstack[MAXN];     


vector<int> children[MAXN];


int fenwSize;


inline void bit_update(int i, int delta) {
    for(; i < fenwSize; i = i | (i + 1))
        fenw[i] += delta;
}

inline int bit_query(int i) {
    int s = 0;
    for(; i >= 0; i = (i & (i + 1)) - 1)
        s += fenw[i];
    return s;
}

inline int bit_range(int l, int r) {
    return bit_query(r) - (l ? bit_query(l - 1) : 0);
}

int main(){
    int N = readInt(); 
    par[0] = -1;
    for (int i = 1; i <= N; i++){
        int p = readInt();
        par[i] = p;
        children[p].push_back(i);
    }
    
    
    int timer = 0;
    int stackTop = 0;
    dstack[stackTop++] = 0;
    tin[0] = timer++;
    depth[0] = 0;
    memset(childIdx, 0, sizeof(int) * (N+1));
    while(stackTop){
        int v = dstack[stackTop - 1];
        if(childIdx[v] < (int)children[v].size()){
            int child = children[v][childIdx[v]++];
            depth[child] = depth[v] + 1;
            tin[child] = timer++;
            dstack[stackTop++] = child;
        } else {
            tout[v] = timer - 1;
            stackTop--;
        }
    }
    fenwSize = timer;
    for (int i = 0; i < fenwSize; i++)
        fenw[i] = 0;
    
    
    int M = 0;
    for (int i = 1; i <= N; i++){
        if(children[i].empty()){
            M++;
            int pos = tin[i];
            for(; pos < fenwSize; pos = pos | (pos + 1))
                fenw[pos]++;
        }
    }
    
    
    for (int i = 0; i <= N; i++)
        up[0][i] = par[i];
    for (int j = 1; j < LOGN; j++){
        for (int i = 0; i <= N; i++){
            int p = up[j-1][i];
            up[j][i] = (p == -1 ? -1 : up[j-1][p]);
        }
    }
    
    
    
    for (int qi = 0; qi < M; qi++){
        int q = readInt();
        
        
        int candidate = q;
        
        for (int j = LOGN - 1; j >= 0; j--){
            int anc = up[j][candidate];
            if(anc == -1) continue;
            
            if(bit_range(tin[anc], tout[anc]) == 1)
                candidate = anc;
        }
        
        
        printf("%d\n", depth[candidate]);
        
        int pos = tin[q];
        for(; pos < fenwSize; pos = pos | (pos + 1))
            fenw[pos]--;
    }
    
    return 0;
}
