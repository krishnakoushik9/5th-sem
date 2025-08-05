/*

Develop a simple data link layer that performs the 
Flow control using the Sliding Window Protocol and loss recovery using 
the GO - BACK - N Mechanism 

*/
#include <stdio.h>
#include <string.h>
#include <time.h>

#define Total_frames 10
#define Window_size 4
#define Loss_probability 20
int is_frame_lost(){
    return(rand()%100)<Loss_probability;
}
int main(){
    int base = 0,next_seq_num = 0;
    int ack,i;
    srand(time(NULL));
    printf("Sliding Window Protocol with Go-Back-N Mechanism\n");
    while(base < Total_frames){
        printf("\n[Sender] Window:[%d to %d]\n", base, base + Window_size - 1);
        for(i = base; i < base + Window_size && i < Total_frames; i++){
            if(!is_frame_lost()){
                printf("Sending frame %d\n", i);
            } else {
                printf("Frame %d lost\n", i);
            }
        }
        if(i==base + Window_size || i == Total_frames){
            base += Window_size;
            if(base >= Total_frames) {
                base = Total_frames; 
                printf("[Receiver] ACK for frame %d.\n",base -1);
            } else {
                printf("[Receiver] No ACK received for frame %d. GO-BACK-N retransmission\n", base - 1);
                printf("Retransmitting frames from %d to %d\n", base - Window_size, base - 1);
                base -= Window_size; 
            }
        }
    }
    
    printf("\nTransmission completed successfully!\n");
    return 0;
}