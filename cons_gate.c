#include<stdio.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<semaphore.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>
#include<sys/shm.h>
int count=0;
void main(){
        int shmfd;
        sem_t *f,*e,*s;
        int *buff;
	int buffval;
        int i=0;//1st index position of the buffer array
        shmfd=shm_open("p330",O_CREAT | O_RDWR,0666);
        ftruncate(shmfd,5*sizeof(int));//5 is the buffer size
        buff=(int *)mmap(0,5*sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,shmfd,0);
        f=sem_open("f_330",O_CREAT,0666,0);
        e=sem_open("e_330",O_CREAT,0666,5);
        s=sem_open("s_330",O_CREAT,0666,1);
        while(1){
		//while(count==0);no need of this line.it is used to demonstr problem as in lec 3.2
                sem_wait(f);
                sem_wait(s);
		if(buff[i]==-1){
			sem_post(s);
			sem_post(f);
			//break;
                        //buff[i]=-1;
			//exit(0);
                        break;
		}
                printf("CONSUMED item %d at pos %d\n",buff[i],i);
                i=(i+1)%5;
                count=count-1;
                sem_post(s);
                sem_post(e);
                sleep(1);
        }
        sem_close(f);
        sem_close(e);
        sem_close(s);
        close(shmfd);
}





