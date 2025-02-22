#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<pthread.h>

int client[20],i=0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *handleclient(void *arg)
{
  int client_sock=*((int*)arg),n;
  char buf[1024];
  while(1)
    {
     bzero(buf,1024);
     n=recv(client_sock,buf,sizeof(buf),0);
     printf("Message:%s",buf); 
     if(strncmp("exit",buf,4)==0)
     {
       pthread_mutex_lock(&mutex);
       close(client_sock);
       for(int j=0;j<i;j++)
        {
          if(client[j] == client_sock)
           {
             printf("Client[%d] is disconnected\n",j+1);
             for (int k = j;k < i-1; k++) {
                        client[k] = client[k + 1];
                    }
               i--;
               break;           
           }
        }
        if(i<=0)
         {
           exit(0);
         }
       pthread_mutex_unlock(&mutex);  
       break;
     }
     pthread_mutex_lock(&mutex);
     for(int j=0;j<i;j++)
      {
             if(client[j] != client_sock)
              {
                 send(client[j],buf,sizeof(buf),0);
              }         
      }  
     pthread_mutex_unlock(&mutex);       
    }    
    pthread_exit(NULL); 
}

int main(int argc,char **argv)
{
  if(argc != 2)
  {
    printf("Error");
    exit(0);
  }
  int port=atoi(argv[1]);
  pthread_t tid;
  int server_sock,client_sock;
  struct sockaddr_in serveraddr,clientaddr;
  socklen_t addr_size;
  
  server_sock=socket(AF_INET,SOCK_STREAM,0);
  printf("Server is created successfully\n");
  memset(&serveraddr,'\0',sizeof(serveraddr));
  serveraddr.sin_family=AF_INET;
  serveraddr.sin_port=htons(port);
  serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
  
  bind(server_sock,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
  printf("Bind to Port number %d\n",port);
  
  listen(server_sock,5);
  printf("Listening....\n");


  while(1)
   {
    addr_size=sizeof(clientaddr);
    client_sock=accept(server_sock,(struct sockaddr*)&clientaddr,&addr_size);
    pthread_mutex_lock(&mutex);
    client[i++]=client_sock;
    pthread_mutex_unlock(&mutex);
    
     printf("Client[%d] Connected\n",i);    
     pthread_create(&tid,NULL,handleclient,&client_sock);
     sleep(1);
   } 
  
  return 0;
}
