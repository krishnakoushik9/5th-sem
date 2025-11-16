// client.c - IoT Device Simulator (Sender)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    srand(time(0));

    printf("IoT Device started sending data...\n");

    while (1) {
        float temp = 25 + rand() % 15;  // Random temperature (25–40°C)
        float hum = 40 + rand() % 30;   // Random humidity (40–70%)

        sprintf(buffer, "%.2f %.2f", temp, hum);

        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr*)&serverAddr, sizeof(serverAddr));

        printf("Sent -> Temp: %.2f°C, Humidity: %.2f%%\n", temp, hum);
        sleep(2);  // Send every 2 seconds
    }

    close(sockfd);
    return 0;
}
