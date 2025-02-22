#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define SERVER_IP "127.0.0.1"
#define PORT 5106
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    struct hostent *server;
    char file_name[BUFFER_SIZE];
    ssize_t bytes_sent, bytes_received;
    char buffer[BUFFER_SIZE];

    // Create a TCP socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Get the server's IP address
    server = gethostbyname(SERVER_IP);
    if (server == NULL) {
        fprintf(stderr, "Error: no such host\n");
        exit(EXIT_FAILURE);
    }

    // Configure the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    // Get the file name from the user
    printf("Enter file name: ");
    scanf("%s", file_name);

    // Send the file name to the server
    bytes_sent = send(client_socket, file_name, strlen(file_name), 0);
    if (bytes_sent < 0) {
        perror("send");
        exit(EXIT_FAILURE);
    }

    // Receive the server's response
    bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received < 0) {
        perror("recv");
        exit(EXIT_FAILURE);
    }

    buffer[bytes_received] = '\0';
    printf("%s\n", buffer);

    // Close the socket
    close(client_socket);

    return 0;
}
