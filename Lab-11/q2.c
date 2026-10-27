#include <stdio.h>
#include <stdlib.h>
int main(void){
    int n,m,K,R;
    printf("Enter n m K R: ");
    if(scanf("%d %d %d %d",&n,&m,&K,&R)!=4) return 1;
    int *hub=malloc(K*sizeof(int));
    printf("Enter %d hub vertices (in order h1..hK): ",K);
    for(int i=0;i<K;i++) scanf("%d",&hub[i]);
    int *head=malloc((n+1)*sizeof(int)),*nxt=malloc(2*m*sizeof(int)+4),*to=malloc(2*m*sizeof(int)+4);
    for(int i=1;i<=n;i++) head[i]=-1;
    int ec=0;
    printf("Enter %d edges (u v):\n",m);
    for(int i=0;i<m;i++){
        int u,v; scanf("%d %d",&u,&v);
        to[ec]=v; nxt[ec]=head[u]; head[u]=ec++;
        to[ec]=u; nxt[ec]=head[v]; head[v]=ec++;
    }
    int *dist=malloc((n+1)*sizeof(int)),*owner=malloc((n+1)*sizeof(int)),*q=malloc((n+1)*sizeof(int));
    for(int i=1;i<=n;i++){dist[i]=-1;owner[i]=-1;}
    int f=0,b=0;
    for(int i=0;i<K;i++){                 /* all hubs at distance 0; smaller index wins if repeated */
        int h=hub[i];
        if(dist[h]==-1){dist[h]=0;owner[h]=i+1;q[b++]=h;}
    }
    while(f<b){
        int u=q[f++];
        if(dist[u]==R) continue;          /* do not expand beyond radius R */
        for(int e=head[u];e!=-1;e=nxt[e]){
            int v=to[e];
            if(dist[v]==-1){ dist[v]=dist[u]+1; owner[v]=owner[u]; q[b++]=v; }
            else if(dist[v]==dist[u]+1 && owner[u]<owner[v]) owner[v]=owner[u]; /* tie-break: smallest index */
        }
    }
    printf("\nVertex : Owner Dist\n");
    for(int v=1;v<=n;v++){
        if(dist[v]==-1) printf("%d : -1 (outside coverage)\n",v);
        else printf("%d : %d %d\n",v,owner[v],dist[v]);
    }
    return 0;
}