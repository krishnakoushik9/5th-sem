#include<stdio.h>
#include<string.h>
#define INF 9999

int main(){
    int u,v,num,i,j,min,n;
    int s[20],dist[20],path[20];
    int cost[20][20];
    printf("Enter no.of Vertices: ");
    scanf("%d",&n);
    printf("Enter the Adjacency matrix(-1 for no edge) \n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d",&cost[i][j]);
            if(i==j){
                cost[i][j]=0;
            }else if(cost[i][j]==-1){
                cost[i][j]=INF;
            }
        }
    }
    printf("Enter source vertex(0 to %d): ",n-1);
    scanf("%d",&v);
    for(i=0;i<n;i++){
        s[i]=0;
        path[i]=v;
        dist[i]=cost[v][i];
    }    
    dist[v]=0;
    s[v]=1;
    for(num = 1;num<n;num++){
        min = INF;
        u=-1;
        for(i=0;i<n;i++){
            if(!s[i] && dist[i] < min){
                min = dist[i];
                u=i;
            }
        }
        if(u==-1){
            break;
        }
        s[u] = 1;
        for(i=0;i<n;i++){
            if(!s[i] && dist[i] > dist[u] + cost[u][i]){
                dist[i] = dist[u] + cost[u][i];
                path[i] = u;
            }
        }
    }
    printf("\n Vertex \t Distance \t Path \n");
    for(i=0;i<n;i++){
        if(dist[i] == INF){
            printf("%d\t INF\t\tNO Path\n",i);
        }
        else{
            printf("%d\t%d\t\t",i,dist[i]);
            j=i;
            printf("%d",j);
            while(path[j]!=v){
                j = path[j];
                printf("<- %d",j);
            }
            printf("<- %d",v);
            printf("\n");
        }
    }
    return 0;
}
