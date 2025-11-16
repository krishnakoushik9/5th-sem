#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_FRAMES 10
#define WINDOW_SIZE 4
#define LOSS_PROBABILITY 20

int is_frame_lost() {
    return (rand() % 100) < LOSS_PROBABILITY;
}

int main() {
    srand(time(NULL));
    int base = 0;

    printf("Simulating Go-Back-N ARQ...\n\n");
    while (base < TOTAL_FRAMES) {
        printf("Current window: [%d to %d]\n", base, base + WINDOW_SIZE - 1);
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            printf("Sending frame %d\n", i);
            if (is_frame_lost()) {
                printf("Frame %d lost! Retransmitting from %d...\n\n", i, i);
                base = i;
                break;
            } else {
                printf("Frame %d received.\n", i);
            }
        }
        base += WINDOW_SIZE;
    }
    printf("All frames sent.\n");
    return 0;
}
