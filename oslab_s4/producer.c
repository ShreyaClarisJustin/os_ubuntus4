//chechi 
//this is wrang

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/stat.h>
sem_t *f,*e,*s;
int *buffer;
int main()
{
   int fd,n=6,item=0,p=5;
   fd=shm_open("pc66",O_CREAT|O_RDWR,0666);
   ftruncate(fd,n*sizeof(int));
   buffer=(int *)mmap(NULL,n*sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
   f=sem_open("f66",O_CREAT,0666,0);
   e=sem_open("e66",O_CREAT,0666,n);
   s=sem_open("s66",O_CREAT,0666,1);
   while(1)
   {
      sem_wait(e);
      sem_wait(s);
      buffer[item]=p;
      printf("Produced itm:%d ",buffer[item]);
      sem_post(s);
      item=(item+1)%n;
      p+=6;
      sem_post(f);
      sleep(1);
   }
   sem_close(f);
   sem_close(e);
   sem_close(s);
   shm_unlink("pc66");
}
