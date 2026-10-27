#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXL 16
typedef struct { char s[MAXL]; } Word;
static Word *w; static int *tab, TS, L;
static unsigned long hsh(const char *s){ unsigned long h=5381; while(*s) h=h*33+(unsigned char)*s++; return h; }
static int find(const char *s){
    unsigned long i=hsh(s)%TS;
    while(tab[i]!=-1){ if(strcmp(w[tab[i]].s,s)==0) return tab[i]; i=(i+1)%TS; }
    return -1;
}
static void insert(const char *s,int id){
    unsigned long i=hsh(s)%TS;
    while(tab[i]!=-1) i=(i+1)%TS;
    tab[i]=id;
}
int main(void){
    int N; char A[MAXL],B[MAXL];
    printf("Enter N: "); if(scanf("%d",&N)!=1) return 1;
    w=malloc((N+2)*sizeof(Word));
    TS=2*(N+2)+1; tab=malloc(TS*sizeof(int));
    for(int i=0;i<TS;i++) tab[i]=-1;
    int cnt=0;
    printf("Enter %d dictionary words:\n",N);
    for(int i=0;i<N;i++){
        char t[MAXL]; scanf("%15s",t);
        if(find(t)==-1){ strcpy(w[cnt].s,t); insert(t,cnt); cnt++; }
    }
    printf("Enter start word A and target word B: ");
    scanf("%15s %15s",A,B);
    L=strlen(A);
    if(strlen(B)!=(size_t)L){ printf("-1\n"); return 0; }
    int tb=find(B);
    if(tb==-1){ printf("Minimum mutations: -1 (B not in dictionary)\n"); return 0; }
    int sa=find(A);
    if(sa==-1){ strcpy(w[cnt].s,A); insert(A,cnt); sa=cnt++; }
    if(sa==tb){ printf("Minimum mutations: 0\n"); return 0; }

    int *dA=malloc(cnt*sizeof(int)),*dB=malloc(cnt*sizeof(int));
    for(int i=0;i<cnt;i++) dA[i]=dB[i]=-1;
    int *fa=malloc(cnt*sizeof(int)),*fb=malloc(cnt*sizeof(int)),*nx=malloc(cnt*sizeof(int));
    int na=1,nb=1; fa[0]=sa; dA[sa]=0; fb[0]=tb; dB[tb]=0;
    int ans=-1;
    while(na>0&&nb>0&&ans<0){
        int fromA = (na<=nb);                         /* expand the smaller frontier */
        int *F = fromA?fa:fb, *dm = fromA?dA:dB, *dot = fromA?dB:dA;
        int sz = fromA?na:nb, nn=0, best=-1;
        for(int i=0;i<sz;i++){
            int u=F[i]; char t[MAXL]; strcpy(t,w[u].s);
            for(int p=0;p<L;p++){
                char orig=t[p];
                for(char c='a';c<='z';c++){
                    if(c==orig) continue;
                    t[p]=c;
                    int v=find(t);
                    if(v==-1) continue;
                    if(dot[v]!=-1){ int tot=dm[u]+1+dot[v]; if(best<0||tot<best) best=tot; }
                    else if(dm[v]==-1){ dm[v]=dm[u]+1; nx[nn++]=v; }
                }
                t[p]=orig;
            }
        }
        if(best>=0){ ans=best; break; }               /* min over the whole level is exact */
        memcpy(F,nx,nn*sizeof(int));
        if(fromA) na=nn; else nb=nn;
    }
    printf("Minimum mutations: %d\n",ans);
    return 0;
}