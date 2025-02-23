#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
typedef struct server
{
	int server_up;
	int client_up;
	int read_write;
	char msg[20];
} node;
node *p;
int main(){
	int fd;
	fd=shm_open("schl",O_CREAT|O_RDWR,0666);
	ftruncate(fd,sizeof(node));
	p=(node *)mmap(NULL,sizeof(node),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	while(1)
	{
		while(p->server_up==1)
		{
			printf("message from server:%s\n",p->msg);
			//p->client_up=1;
			p->server_up=0;
		}
		printf("enter the mesage from client: ");
		scanf("%s\n",p->msg);
		p->client_up=1;
		p->read_write=0;
		if(p->msg[0]=='e')
		{
			exit(0);
		}
		sleep(1);
		while(p->read_write!=1);
	}
	munmap(NULL,sizeof(node));
	shm_unlink("scl");
}
