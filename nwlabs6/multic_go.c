#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<pthread.h>

void *receivemessage(void *arg)
{
    int clientsock=*((int*)arg);
    char buf[1024];
   while(1)
    { 
    bzero(buf,1024);
    recv(clientsock,buf,sizeof(buf),0);
    printf("Message:%s",buf);
    if(strncmp(buf,"exit",4)==0)
     {
       printf("Disconnected\n");
       pthread_exit(NULL);
       close(clientsock);
       break;
     }
   } 
   
   pthread_exit(NULL);
}

void main(int argc,char **argv)
{
  if(argc != 2)
   {
     printf("Error");
     exit(0);
   }
  int port=atoi(argv[1]); 
  int clientsock; 
  struct sockaddr_in addr;
  pthread_t tid;
  char buf[1024];
  
  clientsock=socket(AF_INET,SOCK_STREAM,0);
  printf("Client is created succesfully\n");
  memset(&addr,'\0',sizeof(addr));
  addr.sin_family=AF_INET;
  addr.sin_port=htons(port);
  addr.sin_addr.s_addr=inet_addr("127.0.0.1");
  
     connect(clientsock,(struct sockaddr*)&addr,sizeof(addr)); 
     printf("Connection Established successfully\n");
    
   pthread_create(&tid,NULL,receivemessage,&clientsock);
    
   while(1)
   {
    printf("Enter message\n");
    fgets(buf,sizeof(buf),stdin);
    send(clientsock,buf,strlen(buf),0);
    
    if(strncmp(buf,"exit",4)==0)
     {
       printf("Disconnected\n");
       close(clientsock);
       break;
     }
   } 
       

}
