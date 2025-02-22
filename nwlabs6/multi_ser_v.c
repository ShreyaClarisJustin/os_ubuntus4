//vee correct
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 12345
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

void *handle_client(void *arg);

typedef struct {
    int client_socket;
    struct sockaddr_in client_address;
} client_info;

client_info clients[MAX_CLIENTS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
    int server_socket;
    struct sockaddr_in server_address;

    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error in socket creation");
        exit(EXIT_FAILURE);
    }

    // Prepare server address
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);

    // Bind server socket to address
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Error in binding");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("Error in listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Accept incoming connections and handle them using threads
    while (1) {
        int client_socket;
        struct sockaddr_in client_address;
        socklen_t client_address_len = sizeof(client_address);

        // Accept connection from client
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_len);
        if (client_socket < 0) {
            perror("Error in accept");
            exit(EXIT_FAILURE);
        }

        printf("Client connected\n");

        // Add client information to clients array
        pthread_mutex_lock(&mutex);
        int i;
        for (i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i].client_socket == 0) {
                clients[i].client_socket = client_socket;
                clients[i].client_address = client_address;
                break;
            }
        }
        pthread_mutex_unlock(&mutex);

        if (i == MAX_CLIENTS) {
            printf("Maximum number of clients reached. No longer accepting connections.\n");
            close(client_socket);
        } else {
            // Create thread to handle client
            pthread_t thread_id;
            if (pthread_create(&thread_id, NULL, handle_client, (void*)&clients[i]) != 0) {
                perror("Error in thread creation");
                exit(EXIT_FAILURE);
            }
        }
    }

    // Close server socket
    close(server_socket);

    return 0;
}

void *handle_client(void *arg) {
    client_info *client = (client_info*)arg;
    int client_socket = client->client_socket;
    struct sockaddr_in client_address = client->client_address;
    char buffer[BUFFER_SIZE];

    // Receive and broadcast messages
    while (1) {
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received < 0) {
            perror("Error in receiving");
            break;
        } else if (bytes_received == 0) {
            printf("Client disconnected\n");
            break;
        } else {
            buffer[bytes_received] = '\0';

            // Broadcast message to all clients
            pthread_mutex_lock(&mutex);
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (clients[i].client_socket != 0 && clients[i].client_socket != client_socket) {
                    if (send(clients[i].client_socket, buffer, strlen(buffer), 0) < 0) {
                        perror("Error in sending");
                    }
                }
            }
            pthread_mutex_unlock(&mutex);
        }
    }

    // Remove client from clients array
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].client_socket == client_socket) {
            clients[i].client_socket = 0;
            break;
        }
    }
    pthread_mutex_unlock(&mutex);

    // Close client socket
    close(client_socket);

    return NULL;
}
