//j not broadcast.coorect code.in fair record
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include <pthread.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include<string.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

typedef struct {
    int id;
    int socket;
    struct sockaddr_in address;
    pthread_t thread;
} Client;

Client clients[MAX_CLIENTS];
int client_count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *handle_client(void *arg);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(atoi(argv[1]));

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Socket bind failed");
        close(server_socket);
        return 1;
    }

    if (listen(server_socket,5)==-1){
        perror("Socket listen failed");
        close(server_socket);
        return 1;
    }

    printf("Server started. Waiting for connections...\n");

    while (1) {
        client_socket=accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("Accept failed");
            continue;
        }

        pthread_mutex_lock(&mutex);
        if (client_count < MAX_CLIENTS) {
            Client *client = &clients[client_count++];
            client->id = client_count;
            client->socket = client_socket;
            client->address = client_addr;

            if (pthread_create(&client->thread,NULL,handle_client,(void *)client) != 0) {
                perror("Thread creation failed");
                close(client_socket);
                client_count--;
            }
        } else {
            printf("Maximum clients reached. Connection rejected.\n");
            close(client_socket);
        }
        pthread_mutex_unlock(&mutex);
    }

    close(server_socket);
    return 0;
}
void *handle_client(void *arg) {
    Client *client = (Client *)arg;
    char buffer[BUFFER_SIZE];

    printf("New client connected: %s:%d\n", inet_ntoa(client->address.sin_addr), ntohs(client->address.sin_port));

    while (1)
    {
        int bytes_received = recv(client->socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0)
        {
            printf("Client %d disconnected.\n", client->id);
            break;
        }
        buffer[bytes_received] = '\0'; // Ensure the received buffer is null-terminated

        char message_buffer[BUFFER_SIZE + 10]; // Add space for appending client ID
        snprintf(message_buffer, sizeof(message_buffer), "%s %d",buffer,client->id); // Append sender client ID to message

        char *token = strtok(message_buffer, " ");
        if (token != NULL)
        {
            int dest_client_id = atoi(token);
            char *message = strtok(NULL, "\n");
            if (message != NULL)
            {
                pthread_mutex_lock(&mutex);
                for (int i = 0; i < client_count; i++)
                {
                    if (clients[i].id == dest_client_id)
                    {
                        // Include sender client ID in the message
                        snprintf(buffer, BUFFER_SIZE, "%d: %s",client->id,message);
                        send(clients[i].socket, buffer, strlen(buffer), 0);
                        break;
                    }
                }
                pthread_mutex_unlock(&mutex);
            }
        }
    }
    close(client->socket);
    pthread_exit(NULL);
}
