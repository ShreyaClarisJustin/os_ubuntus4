#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#define port 5001
int main(){
        int server_sock,client_sock;
        struct sockaddr_in server_addr,client_addr;
        socklen_t addr_size;
        char buff[1024];
	int i,j,c[10][10];

        server_sock=socket(AF_INET,SOCK_STREAM,0);
        memset(&server_addr,'\0',sizeof(server_addr));
        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(port);
        server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
        int n;
        n=bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
        if(n<0){
                printf("bind error");
        }
        else{
                listen(server_sock,5);
                printf("listening\n");
        }

        addr_size=sizeof(client_addr);
        client_sock=accept(server_sock,(struct sockaddr*)&client_addr,&addr_size);
	printf("client connection success\n");
                //bzero(buff,1024);
	int m1,n1,m2,n2;
        int a[10][10],b[10][10];
     	recv(client_sock,&m1,sizeof(m1),0);
	printf("%d ",m1);
        recv(client_sock,&n1,sizeof(n1),0);
	printf("%d\n",n1);
	for(i=0;i<m1;i++){
                for(j=0;j<n1;j++){
			recv(client_sock,&(a[i][j]),sizeof(a[i][j]),0);
                        printf("%d",a[i][j]);
                }
        }
	printf("\nreceived matrix A successfully\n");
        //send(client_sock,buff,strlen(buff),0);
        
	recv(client_sock,&m2,sizeof(m2),0);
        recv(client_sock,&n2,sizeof(n2),0);
	printf("Received matrix B dimensions: %d x %d\n", m2, n2);
        for(i=0;i<m2;i++){
                for(j=0;j<n2;j++){
			recv(client_sock,&(b[i][j]),sizeof(b[i][j]),0);
                        printf("%d ",b[i][j]);
                }
        }         
	printf("\n received matrix b succesfully from client");

	int k;
	for(i=0;i<m1;i++){
		for(j=0;j<n2;j++){
			c[i][j]=0;
			for(k=0;k<n1;k++)
				c[i][j]=c[i][j]+(a[i][k]*b[k][j]);
		}
	}
	printf("the product is:\n");
	for(i=0;i<m1;i++){
                for(j=0;j<n2;j++){
			send(client_sock,&(c[i][j]),sizeof(c[i][j]),0);
                        //printf("%d",c[i][j]);
                }
        }
        return 0;
}

