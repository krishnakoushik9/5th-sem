// server.c - IoT Analytics Server (Receiver + Analyzer)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[1024];
    socklen_t addr_size;
    float temp_sum = 0, hum_sum = 0;
    int count = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket error");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind error");
        exit(1);
    }

    printf("IoT Analytics Server Running on Port %d...\n", PORT);

    while (1) {
        addr_size = sizeof(clientAddr);
        int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                         (struct sockaddr*)&clientAddr, &addr_size);
        buffer[n] = '\0';

        float temp, hum;
        sscanf(buffer, "%f %f", &temp, &hum);

        temp_sum += temp;
        hum_sum += hum;
        count++;

        float avg_temp = temp_sum / count;
        float avg_hum = hum_sum / count;

        printf("Device Data -> Temp: %.2f°C, Humidity: %.2f%%\n", temp, hum);
        printf("Average so far -> Temp: %.2f°C, Humidity: %.2f%%\n\n",
               avg_temp, avg_hum);

        // Simple Alert Logic (Prescriptive Analytics)
        if (temp > 35.0)
            printf("⚠️  ALERT: High temperature detected!\n\n");
    }

    close(sockfd);
    return 0;
}
