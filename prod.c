#include<stdio.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<semaphore.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>
#include<sys/shm.h>
typedef struct{
	char buff[100];
	int status;
	int i;
}node;
node *pt;
void main(){
        int shmfd;
        int k=1;
        sem_t *f,*e,*s;
        
        //int i=0;//1st index position of the buffer array
        shmfd=shm_open("pc4611",O_CREAT | O_RDWR,0666);
        ftruncate(shmfd,5*sizeof(int));//5 is the buffer size
        pt=(node *)mmap(0,5*sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,shmfd,0);
        f=sem_open("f_46",O_CREAT,0666,0);
        e=sem_open("e_46",O_CREAT,0666,5);
        s=sem_open("s_46",O_CREAT,0666,1);
	pt->status=1,pt->i=0;
        while(1){
		//if(pt->status==1){
                sem_wait(e);
                sem_wait(s);
		pt->buff[pt->i]=k;
                printf("PRODUCED item %d at pos %d\n",pt->buff[pt->i],pt->i);
		pt->i=((pt->i)+1)%5;
                k++;
                sem_post(s);
                sem_post(f);
		//pt->status=0;
		
                sleep(1);
		}
	}
        sem_close(f);
        sem_close(e);
        sem_close(s);
        close(shmfd);
}
