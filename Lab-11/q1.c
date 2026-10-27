#include <stdio.h>
#include <stdlib.h>
#define INF 1000000000
int main(void){
    int n,m,S; long long C;
    printf("Enter n m S C: ");
    if(scanf("%d %d %d %lld",&n,&m,&S,&C)!=4) return 1;
    int *head=malloc((n+1)*sizeof(int)),*nxt=malloc(m*sizeof(int)),*to=malloc(m*sizeof(int)),*wt=malloc(m*sizeof(int));
    for(int i=1;i<=n;i++) head[i]=-1;
    printf("Enter %d edges (u v w), w in {0,1}:\n",m);
    for(int i=0;i<m;i++){
        int u,v,w; scanf("%d %d %d",&u,&v,&w);
        to[i]=v; wt[i]=w; nxt[i]=head[u]; head[u]=i;
    }
    /* state id = v*2+p ; p = parity of number of weight-1 edges used.
       Since weights are 0/1, W(P)=k1(P), so p = W mod 2. dist = min W for that parity. */
    int *dist=malloc(2*(n+1)*sizeof(int));
    for(int i=0;i<2*(n+1);i++) dist[i]=INF;
    int cap=2*m+4, *dq=malloc((2*cap+2)*sizeof(int));
    int f=cap,b=cap;                  /* deque occupies dq[f..b-1] */
    dist[S*2]=0; dq[b++]=S*2;
    while(f<b){
        int s=dq[f++]; int u=s>>1,p=s&1, d=dist[s];
        for(int e=head[u];e!=-1;e=nxt[e]){
            int v=to[e], np=p^wt[e], t=v*2+np, nd=d+wt[e];
            if(nd<dist[t]){
                dist[t]=nd;
                if(wt[e]==0) dq[--f]=t; else dq[b++]=t;
            }
        }
    }
    printf("\nVertex : MinCost\n");
    for(int v=1;v<=n;v++){
        long long best=-1;
        if(dist[v*2]<INF) best=dist[v*2];                       /* even parity: no penalty */
        if(dist[v*2+1]<INF){ long long c=dist[v*2+1]+C; if(best<0||c<best) best=c; }
        if(best<0) printf("%d : unreachable\n",v); else printf("%d : %lld\n",v,best);
    }
    return 0;
}