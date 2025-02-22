#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<sys/ipc.h>
#include<sys/shm.h>
struct shared_memory
{
   int data;//data=1 means data written else data read;
   int exit;
   char message[50]; 
};
struct shared_memory * sharedBUFFER;
int main()
{
   int i=0;
   char message[50];
   //struct shared_memory * sharedBUFFER;
   int fd=shm_open("new123",O_CREAT|O_RDWR,0666);
   if(fd>0){
	 ftruncate(fd,sizeof(struct shared_memory));
         sharedBUFFER=(struct shared_memory *)mmap(0,sizeof(struct shared_memory),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
         do
         {
            printf("\n--------------------------");
            printf("\nEnter the message,Type STOP to exit:\n");
	    //sharedBUFFER->data=1;
            //scanf("%s",message);
            fgets(message,sizeof(message), stdin);
            message[strcspn(message, "\n")] = 0;  
            if(strcmp(message,"STOP")==0)
            {
               i=1;
               sharedBUFFER->data=1;
               sharedBUFFER->exit=1;
               printf("Exit request sent.Waiting for EXIT confirmation.\n");
               while(sharedBUFFER->data==1);
               munmap(sharedBUFFER,sizeof(struct shared_memory));
               close(fd);
               shm_unlink("new123");
               printf("Exiting the receiver program\n");
               break;
            }
            else
            {
              strcpy(sharedBUFFER->message,message);
              sharedBUFFER->data=1;//1 means sending msg
              sharedBUFFER->exit=0;
              //printf("\nThe received message is \"%s\"\n",message);
            }
            printf("\n--------------");
             printf("Waiting for the message:\n");
            while(sharedBUFFER->data==0);
            printf("Interpreting the message received.\n");
            if(sharedBUFFER->exit==1)
            {
               printf("Exit message received\n");
               i=1;
               sharedBUFFER->data=0;
               sharedBUFFER->exit=0;
               //printf("Exit request sent.Waiting for EXIT confirmation\n");
               //while(sharedBUFFER->data==0);
               munmap(sharedBUFFER,sizeof(struct shared_memory));
               close(fd);
               shm_unlink("new123");
               printf("Exiting the receiver program\n");
               break;
            }
            else
            {
              strcpy(message,sharedBUFFER->message);
              sharedBUFFER->data=0;
              sharedBUFFER->exit=0;
              printf("\nThe received message is \"%s\"\n",message);
            }
         }while(i==0);
   }
   else
   {
      printf("Error in creating shared memory area\n");
   }
   return(0);
}
