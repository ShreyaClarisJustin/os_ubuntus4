//jeethu correct code.in record
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void *receive_messages(void *arg);

int main(){
    /*if (argc != 3) {
        printf("Usage: %s <server_ip> <port>\n", argv[0]);
        return 1;
    }*/
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    client_socket=socket(AF_INET,SOCK_STREAM,0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    if(connect(client_socket,(struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(client_socket);
        return 1;
    }

    printf("Connected to server. Start chatting...\n");

    pthread_t recv_thread;
    if (pthread_create(&recv_thread, NULL, receive_messages, (void *)&client_socket) != 0) {
        perror("Thread creation failed");
        close(client_socket);
        return 1;
    }

    while(1){
        fgets(buffer, BUFFER_SIZE, stdin);


        if (send(client_socket, buffer, strlen(buffer),0)==-1){
            perror("Send failed");
            break;
        }
    }
    close(client_socket);
    return 0;
}
void *receive_messages(void *arg) {
    int client_socket=*((int *)arg);
    char buffer[BUFFER_SIZE];

    while (1) {
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if(bytes_received<=0){
            printf("Disconnected from server.\n");
            break;
        }
        buffer[bytes_received] = '\0';

        int sender_client_id;
        sscanf(buffer, "%d: %[^\n]", &sender_client_id, buffer); // Extract sender client ID

        printf("from %d: %s\n", sender_client_id, buffer); // Print sender client ID along with message
    }

    pthread_exit(NULL);
}
