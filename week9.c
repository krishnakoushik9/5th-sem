#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int frame_no;
    char data[256];
}Frame;
int compare (const void *a, const void *b) {
    return ((Frame*)a)->frame_no - ((Frame*)b)->frame_no;
}
int main() {
    int n;
    printf("Enter the number of frames: ");
    scanf("%d", &n);
    getchar(); // Consume the newline character
    Frame buffer[n];
    printf("Enter the frame numbers and data (out of order):\n");
    for(int i = 0; i < n; i++) {
        printf("Frame %d number: ", i + 1);
        scanf("%d", &buffer[i].frame_no);
        getchar(); // Consume the newline character
        printf("Data: ");
        fgets(buffer[i].data, sizeof(buffer[i].data), stdin);
        // Remove trailing newline if present
        size_t len = strlen(buffer[i].data);
        if (len > 0 && buffer[i].data[len-1] == '\n') {
            buffer[i].data[len-1] = '\0';
        }
    }
    qsort(buffer, n, sizeof(Frame), compare);
    printf("\nSorted Frame\n");
    for(int i = 0; i < n; i++) {
        printf("Frame %d:%s\n", buffer[i].frame_no, buffer[i].data);
    }
    return 0;
}
// Program to simulate frame reordering using a buffer