//sent by sam from go
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/time.h>
#define port 3001

typedef struct {
    int seq_num;
    char data[1024];
    int flag;
} packet;

packet send_packet, recv_ack;

int main(){ 
	int clientsock,i=0; 
  	struct sockaddr_in addr;
  	fd_set readfds;
	socklen_t addr_size;

  	char word[] ="abcdefghijkl";

  	clientsock=socket(AF_INET,SOCK_DGRAM,0);
  	printf("Client is created succesfully\n");
  	memset(&addr,'\0',sizeof(addr));

  	addr.sin_family=AF_INET;
  	addr.sin_port=htons(port);
  	addr.sin_addr.s_addr=inet_addr("127.0.0.1");

  	int base=0,window_size=3,j=0,flag=0;
  	int length=strlen(word);
  	addr_size=sizeof(addr);

	while(1){
		for(int i=base;i<window_size;i++){
			send_packet.data[i]=word[i];
			if(window_size > strlen(word)){
				flag=1;
				send_packet.flag=1;
			}
		}
		send_packet.seq_num=j++;
         	sendto(clientsock,&send_packet,sizeof(send_packet),0,(struct sockaddr*)&addr,addr_size);
         	printf("Frame sent\n");

    	 	FD_ZERO(&readfds);
    	 	FD_SET(clientsock, &readfds);
   	 	struct timeval timeout;
   	 	timeout.tv_sec = 3;
   	 	timeout.tv_usec = 0;

		int a = select(clientsock+1, &readfds, NULL, NULL, &timeout);
         	if(a==-1){
        		perror("select");
        		exit(0);
     		}
     		else if(a==0){
       			printf("Timeout occurred. No data received from server.\n");
        		window_size=3*(send_packet.seq_num+1);
        		j=send_packet.seq_num;
        		base=window_size-3;
        		length=length+3;
        	}
        	else{
           	        recvfrom(clientsock,&recv_ack,sizeof(recv_ack),0,(struct sockaddr*)&addr,&addr_size);
                        printf("Received acknowledgment for sequence number: %d\n", recv_ack.seq_num); 
                        base=window_size;
                        if(length<=3){
                           window_size=length;
                        }
                        else{
                             window_size=window_size+3;
                       	     length=length-3;
                        }
		}
    		if(flag==1)
    		{
    		   close(clientsock);
    		   exit(0);
    		}
    }

    return 0;
}


