#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define PORT 3001
#define WINDOW_SIZE 3
#define TIMEOUT 3

typedef struct {
    int seq_num;
    char data[1024];
    int flag;
} packet;

packet send_packet, recv_ack;

int main() {
    int clientsock;
    struct sockaddr_in addr;
    fd_set readfds;
    socklen_t addr_size;
    char word[] = "abcdefghijkl";
    int base = 0, next_seq_num = 0, length = strlen(word);
    int flag = 0;

    clientsock = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientsock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Client is created successfully\n");

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr_size = sizeof(addr);

    while (1) {
        for (int i = 0; i < WINDOW_SIZE && next_seq_num < length; i++) {
            send_packet.seq_num = next_seq_num;
            strncpy(send_packet.data, word + next_seq_num, 1);
            send_packet.data[1] = '\0';
            send_packet.flag = (next_seq_num == length - 1) ? 1 : 0;

            sendto(clientsock, &send_packet, sizeof(send_packet), 0, (struct sockaddr*)&addr, addr_size);
            printf("Frame sent: %s, seq_num: %d\n", send_packet.data, send_packet.seq_num);

            next_seq_num++;
        }

        FD_ZERO(&readfds);
        FD_SET(clientsock, &readfds);
        struct timeval timeout;
        timeout.tv_sec = TIMEOUT;
        timeout.tv_usec = 0;

        int activity = select(clientsock + 1, &readfds, NULL, NULL, &timeout);

        if (activity == -1) {
            perror("select");
            close(clientsock);
            exit(EXIT_FAILURE);
        } else if (activity == 0) {
            printf("Timeout occurred. No acknowledgment received.\n");
            next_seq_num = base;
        } else {
            recvfrom(clientsock, &recv_ack, sizeof(recv_ack), 0, (struct sockaddr*)&addr, &addr_size);
            printf("Received acknowledgment for sequence number: %d\n", recv_ack.seq_num);
            base = recv_ack.seq_num + 1;

            if (recv_ack.flag == 1) {
                printf("All packets acknowledged. Closing connection.\n");
                close(clientsock);
                exit(EXIT_SUCCESS);
            }
        }
    }

    return 0;
}
