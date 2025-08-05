#include<stdio.h>
#include<string.h>  

int main() {
    char input[100], stuffed[200];
    char start_delim, end_delim;
    int i, j = 0;
    
    printf("Enter the data to be stuffed: ");
    scanf("%s", input);
    getchar();
    
    printf("Enter the start delimiter: ");
    scanf("%c", &start_delim);
    getchar();
    
    printf("Enter the end delimiter: ");
    scanf("%c", &end_delim);
    getchar();
    stuffed[j++] = start_delim;
    for(i = 0; i < strlen(input); i++) {
        if(input[i] == start_delim || input[i] == end_delim) {
            stuffed[j++] = input[i];
        }
        stuffed[j++] = input[i];
    }

    stuffed[j++] = end_delim;
    stuffed[j] = '\0';

    printf("Stuffed data: %s\n", stuffed);
    return 0;
}