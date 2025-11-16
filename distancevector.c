#include <stdio.h>
#define INF 999
#define MAX 10

int main() {
    int n, cost[MAX][MAX], dist[MAX][MAX], next_hop[MAX][MAX];
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter connection matrix (999 for no connection):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            dist[i][j] = cost[i][j];
            next_hop[i][j] = j;
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next_hop[i][j] = next_hop[i][k];
                }
            }
        }
    }

    printf("\nRouting Tables:\n");
    for (int i = 0; i < n; i++) {
        printf("\nNode %d:\n", i);
        printf("Destination\tDistance\tNext Hop\n");
        for (int j = 0; j < n; j++) {
            if (i != j) {
                printf("%d\t\t%d\t\t%d\n", j, dist[i][j], next_hop[i][j]);
            }
        }
    }
    return 0;
}
