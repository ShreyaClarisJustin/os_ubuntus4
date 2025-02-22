//chatgpt
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/time.h>

#define PORT 9009
#define MAXLINE 1024
#define TIMEOUT_SEC 10

int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;
    int n, len;

    // Create socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    len = sizeof(cliaddr);

    struct timeval tv;
    tv.tv_sec = TIMEOUT_SEC;
    tv.tv_usec = 0;

    while (1) {
        // Set receive timeout
        if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(tv)) < 0) {
            perror("setsockopt failed");
            exit(EXIT_FAILURE);
        }

        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        if (n < 0) {
            printf("Timeout occurred. No message received.\n");
            continue;  // Wait for the next message
        }

        buffer[n] = '\0';
        printf("Client : %s\n", buffer);

        // Check if the message is "exit"
        if (strcmp(buffer, "exit\n") == 0) {
            printf("Exiting server...\n");
            break;
        }

        // Send acknowledgment to client
        sendto(sockfd, (const char *)"ACK", strlen("ACK"), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
        printf("ACK sent.\n");
    }

    close(sockfd);
    return 0;
}

