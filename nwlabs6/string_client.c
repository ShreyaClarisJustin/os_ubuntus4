#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 5001
#define BUFFER_SIZE 1024

int main() {
    int client_sock;
    struct sockaddr_in addr;
    char buff1[BUFFER_SIZE],buff2[BUFFER_SIZE];
    char result[2 * BUFFER_SIZE];

    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0) {
        perror("Socket creation error");
        exit(1);
    }

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Connection error");
        close(client_sock);
        exit(1);
    }
    printf("Client is connected to the server\n");

    printf("Enter a string1: ");
    fgets(buff1, BUFFER_SIZE, stdin);
    buff1[strcspn(buff1, "\n")] = '\0';  // Remove trailing newline character
    send(client_sock, buff1, strlen(buff1)+1,0);

     printf("Enter a string2: ");
    fgets(buff2, BUFFER_SIZE, stdin);
    buff2[strcspn(buff2, "\n")] = '\0';  // Remove trailing newline character
    send(client_sock, buff2, strlen(buff2)+1,0);

    recv(client_sock, result, sizeof(result), 0);
    printf("The concatenated result is: %s\n", result);

    close(client_sock);
    return 0;
}
