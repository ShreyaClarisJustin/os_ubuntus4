#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<signal.h>
#include<sys/time.h>
#define port 5001
int main(){
	
  int client_sock,i=0,c[10][10];
  struct sockaddr_in addr;
  socklen_t addr_size;

	int m1,n1,m2,n2;
	int a[10][10],b[10][10];
	int j;
	memset(&addr, '\0', sizeof(addr));
  client_sock=socket(AF_INET,SOCK_STREAM,0);
  printf("Client is created succesfully\n");
  memset(&addr,'\0',sizeof(addr));
  addr.sin_family=AF_INET;
  addr.sin_port=htons(port);
  addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(client_sock,(struct sockaddr*)&addr,sizeof(addr));
	printf("enter order of matrix A");
	scanf("%d%d",&m1,&n1);
	send(client_sock,&m1,sizeof(m1),0);
	printf("\n sent m1\n");
	send(client_sock,&n1,sizeof(n1),0);
	printf("enter the elements");
	for(i=0;i<m1;i++){
                for(j=0;j<n1;j++){
                        scanf("%d",&(a[i][j]));
			send(client_sock,&(a[i][j]),sizeof(a[i][j]),0);
                }
        }
	printf("enter the order of matrixB");
	scanf("%d%d",&m2,&n2);
	send(client_sock,&m2,sizeof(m2),0);
        send(client_sock,&n2,sizeof(n2),0);
	printf("enter the elements");
	for(i=0;i<m2;i++){
		for(j=0;j<n2;j++){
			scanf("%d",&(b[i][j]));

			send(client_sock,&(b[i][j]),sizeof(b[i][j]),0);
		}
	}
	for(i=0;i<m1;i++){
                for(j=0;j<n2;j++){
                        recv(client_sock,&(c[i][j]),sizeof(c[i][j]),0);
                        printf("%d",c[i][j]);
                }
        }
}
