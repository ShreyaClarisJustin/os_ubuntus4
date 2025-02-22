//vee correct
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define BUFFER_SIZE 1024

void *receive_messages(void *arg);
void send_messages(int client_socket);

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    pthread_t receive_thread;

    // Create client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error in socket creation");
        exit(EXIT_FAILURE);
    }

    // Prepare server address
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_address.sin_port = htons(PORT);

    // Connect to server
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Error in connection");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    // Create thread to receive messages
    if (pthread_create(&receive_thread, NULL, receive_messages, (void*)&client_socket) != 0) {
        perror("Error in thread creation");
        exit(EXIT_FAILURE);
    }

    // Send messages
    send_messages(client_socket);

    // Close socket
    close(client_socket);

    return 0;
}

void *receive_messages(void *arg) {
    int client_socket = *((int*)arg);
    char buffer[BUFFER_SIZE];

    // Receive messages and display them
    while (1) {
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received < 0) {
            perror("Error in receiving");
            break;
        } else if (bytes_received == 0) {
            printf("Server disconnected\n");
            break;
        } else {
            buffer[bytes_received] = '\0';
            printf("Received from server: %s\n", buffer);
        }
    }

    return NULL;
}

void send_messages(int client_socket) {
    char buffer[BUFFER_SIZE];

    // Send messages
    while (1) {
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        if (strcmp(buffer, "exit\n") == 0) {
            break;
        }
        if (send(client_socket, buffer, strlen(buffer), 0) < 0) {
            perror("Error in sending");
            exit(EXIT_FAILURE);
        }
    }
}
