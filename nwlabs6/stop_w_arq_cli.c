//stop and wait arq with timeout
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/time.h>

#define PORT 9009
#define MAXLINE 1024
#define TIMEOUT_SEC 5

int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;

    // Create socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;

    struct timeval tv;
    tv.tv_sec = TIMEOUT_SEC;
    tv.tv_usec = 0;

    while (1) {
        // Set receive timeout
        if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(tv)) < 0) {
            perror("setsockopt failed");
            exit(EXIT_FAILURE);
        }

        printf("Enter message: ");
        fgets(buffer, MAXLINE, stdin);

        // Check if the message is "exit"
        if (strcmp(buffer, "exit\n") == 0) {
            printf("Exiting client...\n");
            break;
        }

        // Send message to server
        sendto(sockfd, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
        printf("Message sent to server.\n");

        // Receive acknowledgment from server
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)NULL, NULL);
        if (n < 0) {
            printf("Timeout occurred. No acknowledgment received.\n");
            continue;  // Wait for the next message
        }

        buffer[n] = '\0';
        printf("Server : %s\n", buffer);
    }

    close(sockfd);
    return 0;
}

