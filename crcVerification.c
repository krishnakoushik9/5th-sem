#include <stdio.h>
#include <string.h>

int main() {
    char frame[100], divisor[100], temp[100];
    printf("Enter received frame (data + CRC): ");
    scanf("%s", frame);
    printf("Enter polynomial (divisor): ");
    scanf("%s", divisor);

    int frame_len = strlen(frame);
    int divisor_len = strlen(divisor);

    strcpy(temp, frame);
    for (int i = 0; i <= frame_len - divisor_len; i++) {
        if (temp[i] == '1') {
            for (int j = 0; j < divisor_len; j++) {
                temp[i + j] = (temp[i + j] == divisor[j]) ? '0' : '1';
            }
        }
    }

    for (int i = frame_len - divisor_len + 1; i < frame_len; i++) {
        if (temp[i] == '1') {
            printf("Error detected.\n");
            return 0;
        }
    }
    printf("No error detected.\n");
    return 0;
}
