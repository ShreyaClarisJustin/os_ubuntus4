#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

#define PORT 5001
#define BUFFER_SIZE 1024

void reverse_string(char *str) {
    int len = strlen(str);
    for(int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buff1[BUFFER_SIZE],buff2[BUFFER_SIZE];
    char result[2 * BUFFER_SIZE];
    int n;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket creation error");
        exit(1);
    }

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (n < 0) {
        perror("Bind error");
        close(server_sock);
        exit(1);
    }

    listen(server_sock, 5);
    printf("Server is listening on port %d\n", PORT);

    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    if (client_sock < 0) {
        perror("Accept error");
        close(server_sock);
        exit(1);
    }
    printf("Client connection successful\n");

    recv(client_sock, buff1, sizeof(buff1), 0);
    buff1[BUFFER_SIZE - 1] = '\0';  // Ensure null-terminated string
    printf("Received string1: %s\n", buff1);

    recv(client_sock,buff2,sizeof(buff2), 0);
    buff2[BUFFER_SIZE - 1] = '\0';  // Ensure null-terminated string
    printf("Received string2: %s\n", buff2);

    //strcpy(result1,buff1);
    reverse_string(buff1);
    reverse_string(buff2);
    strcpy(result,buff2);
    strcat(result,buff1);

    send(client_sock, result, strlen(result) + 1, 0);

    close(client_sock);
    close(server_sock);
    return 0;
}
