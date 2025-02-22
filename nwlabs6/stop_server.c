//gok code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/time.h>
#define port 2222

typedef struct {
    int seq_num;
    char data[1024];
    int flag;
} packet;

packet recv_packet,ack_packet;
int server_sock,client_sock,n,j=0;
struct sockaddr_in serveraddr,clientaddr;
socklen_t addr_size;

int main()
{
  /*if(argc != 2)
   {
     printf("Error");
     exit(0);
   }
  int port =atoi(argv[1]);*/
  
  server_sock=socket(AF_INET,SOCK_DGRAM,0);
  if(server_sock ==-1)
  {
    printf("Server not created\n");
    exit(0);
  }
  printf("Server is created successfully\n");
  
  memset(&serveraddr,'\0',sizeof(serveraddr));
  serveraddr.sin_family=AF_INET;
  serveraddr.sin_port=htons(port);
  serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
  bind(server_sock,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
  addr_size=sizeof(clientaddr);
  printf("Bind to Port number %d\n",port);

    while (1) {
        if(recvfrom(server_sock,&recv_packet,sizeof(recv_packet),0,(struct sockaddr*)&clientaddr,&addr_size) < 0) {
            perror("recvfrom failed");
            exit(0);
        }
        printf("Frame received %s\n",recv_packet.data);
        printf("Received packet with sequence number: %d\n", recv_packet.seq_num);
        sleep(2);
        ack_packet.seq_num = recv_packet.seq_num;
        if(j!=3)
        {
	        if (sendto(server_sock,&ack_packet,sizeof(ack_packet),0,(struct sockaddr*)&clientaddr,addr_size) < 0) {
            		perror("sendto failed");
            		exit(EXIT_FAILURE);
        	}
        	printf("Sent acknowledgment for sequence number: %d\n", ack_packet.seq_num);
	}
	j++;
        if(recv_packet.flag == 1){
          close(server_sock);
          exit(0);
        }
    }
    return 0;
}
