#include <stdio.h>
#include <string.h>

int main() {
    char data[100], divisor[100], temp[100], rem[100];
    printf("Enter data (frame): ");
    scanf("%s", data);
    printf("Enter polynomial (divisor): ");
    scanf("%s", divisor);

    int data_len = strlen(data);
    int divisor_len = strlen(divisor);

    strcat(data, "0");
    for (int i = 1; i <= divisor_len - 1; i++) {
        strcat(data, "0");
    }

    strcpy(temp, data);
    for (int i = 0; i <= data_len; i++) {
        if (temp[i] == '1') {
            for (int j = 0; j < divisor_len; j++) {
                temp[i + j] = (temp[i + j] == divisor[j]) ? '0' : '1';
            }
        }
    }

    for (int i = 0; i < divisor_len - 1; i++) {
        rem[i] = temp[data_len + i];
    }
    rem[divisor_len - 1] = '\0';

    printf("CRC: %s\n", rem);
    printf("Transmitted Frame: %s%s\n", data, rem);
    return 0;
}
