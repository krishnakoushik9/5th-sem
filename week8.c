//write a program for congestion control using Leaky Bucket algorithm
#include <stdio.h>
#include <stdlib.h>
#define BUCKET_SIZE 10 // Maximum capacity of the bucket

void leaky_bucket(int incoming[], int n, int outputrate) {
    int i, bucketcontent = 0;
    printf("\n%-6s %-10s %-12s %-10s %-12s\n", "Time", "Incoming", "BucketSize", "Outgoing", "Remaining");
    printf("--------------------------------------------------\n");
    
    for(i = 0; i < n; i++) {
        printf("%-6d ", i+1);
        printf("%-10d ", incoming[i]);
        
        // Handle incoming packets
        if(incoming[i] + bucketcontent > BUCKET_SIZE) {
            printf("OVERFLOW    ");  
            int accepted = BUCKET_SIZE - bucketcontent;
            bucketcontent = BUCKET_SIZE;
            printf("%-10d ", accepted);
        } else {
            bucketcontent += incoming[i];
            printf("%-12d ", bucketcontent);
        }
        
        // Handle outgoing packets
        int sent = (bucketcontent < outputrate) ? bucketcontent : outputrate;
        bucketcontent -= sent;
        printf("%-10d %d\n", sent, bucketcontent);
    }
    
    // Handle remaining packets in the bucket
    while(bucketcontent > 0) {
        i++;
        printf("%-6d %-10d %-12d ", i, 0, bucketcontent);
        int sent = (bucketcontent < outputrate) ? bucketcontent : outputrate;
        bucketcontent -= sent;
        printf("%-10d %d\n", sent, bucketcontent);
    }
}

int main() {
    int n, outputrate;
    printf("Enter the number of time units: ");
    scanf("%d", &n);
    int incoming[n];
    printf("\nEnter the size of incoming packets for each time unit:\n");
    for(int i = 0; i < n; i++) {
        printf("Time %d: ", i+1);
        scanf("%d", &incoming[i]);
    }
    printf("\nEnter the output rate (packets per time unit): ");
    scanf("%d", &outputrate);
    leaky_bucket(incoming, n, outputrate);
    
    return 0;
}