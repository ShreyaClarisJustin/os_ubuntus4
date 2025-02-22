#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 3001

typedef struct {
    int seq_num;
    char data[1024];
    int flag;
} packet;

packet recv_packet, ack_packet;

int main() {
    int server_sock;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t addr_size;

    server_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Server is created successfully\n");

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(server_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("Bind failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    printf("Bind to port number %d\n", PORT);

    addr_size = sizeof(clientaddr);

    while (1) {
        if (recvfrom(server_sock, &recv_packet, sizeof(recv_packet), 0, (struct sockaddr*)&clientaddr, &addr_size) < 0) {
            perror("recvfrom failed");
            close(server_sock);
            exit(EXIT_FAILURE);
        }

        printf("Frame received: %s, seq_num: %d\n", recv_packet.data, recv_packet.seq_num);

        ack_packet.seq_num = recv_packet.seq_num;
        ack_packet.flag = recv_packet.flag;

        if (sendto(server_sock, &ack_packet, sizeof(ack_packet), 0, (struct sockaddr*)&clientaddr, addr_size) < 0) {
            perror("sendto failed");
            close(server_sock);
            exit(EXIT_FAILURE);
        }
        printf("Sent acknowledgment for sequence number: %d\n", ack_packet.seq_num);

        if (recv_packet.flag == 1) {
            printf("Last packet received. Closing connection.\n");
            close(server_sock);
            exit(EXIT_SUCCESS);
        }
    }

    return 0;
}
