//Take an example SUBNET of hosts and obtain broadcast tree for the subnet
#include <stdio.h>
#define MAX 10

int a[MAX][MAX], n;
int visited[MAX];
void broadcastTree(int root) {
    int queue[MAX], front = 0, rear = 0;
    for(int i = 0; i < n; i++) {
        visited[i] = 0;
    }
    visited[root] = 1;
    queue[rear++] = root;
    printf("Broadcast Tree starting from node %d:\n", root);
    while(front < rear) {
        int current = queue[front++];
        for(int j = 0; j < n; j++) {
            if(a[current][j] == 1 && !visited[j]) {
                visited[j] = 1;
                queue[rear++] = j;
                printf("Host %d -> %d\n",current + 1,j+1);
            }
        }
    }
}
int main(){
    int i ,j,root;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    printf("Enter the adjacency matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("Enter connecting of %d --> %d::",i+1,j+1);
            scanf("%d", &a[i][j]);
        }
    }
    printf("Enter the root node: ");
    scanf("%d", &root);
    broadcastTree(root - 1);
    return 0;
}