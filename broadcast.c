#include <stdio.h>

int main() {
    int n, adj[10][10], visited[10], queue[10], front = 0, rear = 0;
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter connection matrix (0/1):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    int root;
    printf("Enter root node: ");
    scanf("%d", &root);

    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
    visited[root] = 1;
    queue[rear++] = root;

    while (front < rear) {
        int current = queue[front++];
        for (int i = 0; i < n; i++) {
            if (adj[current][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
                printf("%d -> %d\n", current, i);
            }
        }
    }
    return 0;
}
