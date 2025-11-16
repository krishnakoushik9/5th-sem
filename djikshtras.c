#include <stdio.h>
#define MAX 10
#define INF 9999

int main() {
    int n, cost[MAX][MAX], distance[MAX], visited[MAX], min, nextnode;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (-1 for no edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == -1) cost[i][j] = INF;
        }
    }

    int source;
    printf("Enter source vertex (0 to %d): ", n - 1);
    scanf("%d", &source);

    for (int i = 0; i < n; i++) {
        distance[i] = cost[source][i];
        visited[i] = 0;
    }
    distance[source] = 0;
    visited[source] = 1;

    for (int k = 1; k < n; k++) {
        min = INF;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && distance[i] < min) {
                min = distance[i];
                nextnode = i;
            }
        }
        visited[nextnode] = 1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && (min + cost[nextnode][i]) < distance[i]) {
                distance[i] = min + cost[nextnode][i];
            }
        }
    }

    printf("\nShortest distances from %d:\n", source);
    for (int i = 0; i < n; i++) {
        if (distance[i] == INF) {
            printf("%d -> %d: No path\n", source, i);
        } else {
            printf("%d -> %d: %d\n", source, i, distance[i]);
        }
    }
    return 0;
}
