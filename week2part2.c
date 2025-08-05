#include<stdio.h>
#include<string.h>

int main() {
    int i, j, k, m, n, cl;
    char a[100], b[100], c[200];
    printf("Enter the Polynomials: ");
    scanf("%s", a);
    printf("Enter the CRC Frame(data+crc): ");
    scanf("%s", c);
    n = strlen(a);
    cl = strlen(c);
    for(i=0; i<n; i++) {
        if(a[i]=='1') {
            m = n - i;  
            break;
        }
    }
    for(k=0; k<=cl-m; k++) {
        if(c[k]=='1') {
            for(j=0; j<m; j++) {
                c[k+j] = (a[i+j] == c[k+j]) ? '0' : '1';
            }
        }
    }
    for(i=0; i<cl; i++) {
        if(c[i] == '1') {
            printf("\nError detected in the received message.\n");
            return 1;
        }
    }
    printf("\nMessage is Correct\n");
    return 0;
}