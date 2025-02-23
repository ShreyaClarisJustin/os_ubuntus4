#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<sys/shm.h>
void main(){
	sem_t *mutex,*wrt;
	int readcount=0;
	int fd=shm_open("ww",O_CREAT|O_RDWR,0666);
	char *buff;
	buff=(char *)mmap(NULL,5*sizeof(char),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	mutex=sem_open("mutex",O_CREAT,0666,1);
	wrt=sem_open("wrt",O_CREAT,0666,1);
	while(1){
		sem_wait(mutex);
		readcount++;
		if(readcount==1)
			sem_wait(wrt);
		sem_post(mutex);

		
		printf("value read is %s\n",buff);
		sleep(0.2);

		sem_wait(mutex);
		readcount--;
		if(readcount==0)
			sem_post(wrt);
		sem_post(mutex);
	}
	sem_close(mutex);
	sem_close(wrt);
	close(fd);
	
}
