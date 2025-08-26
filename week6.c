//Write a code for implementing distance vector routing algorithm at each node
#include <stdio.h>
#define INF 9999
int main(){
    int i ,j,nv,sn,noadj,ede1[20],tde1[20][20],min;
    char sv;
    char adver[20],ch;
    printf("Enter the number of Vertices: ");
    scanf("%d",&nv);
    printf("Enter the Source Vertex number and name: ");
    scanf("%d %c",&sn,&sv);
    printf("Enter the no.of Adjacent Vertices to Vertex: ");
    scanf("%d",&noadj);
    for(i = 0; i < noadj; i++){ 
        printf("\n Enter Time Delay and node name: ");
        scanf("%d %c",&ede1[i],&adver[i]);
    }
    for(i = 0;i < noadj;i++){
        printf("\n Enter time delay from %c to all other nodes: ",adver[i]);
        for(j = 0;j < nv;j++){
            //Hey
            scanf("%d",&tde1[i][j]);
        }
    }
    printf("\n Delay\t VIA--VERTEX\n");
    for(i = 0;i < nv;i++){
        min = INF;
        ch = '-';
        for(j = 0;j < noadj;j++){
            if(min > (tde1[j][i] + ede1[j])){
                min = tde1[j][i] + ede1[j];
                ch = adver[j];  
            }
        }
        if(i != sn - 1){
            printf("%d\t%c\n", min, ch);  
        }else{
            printf("0\t-\n");
        }
    }
    return 0;  
}