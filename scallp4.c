
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main(){
	int fd;
	char wr[30]="os lab";
	char rd[30];
	fd=open("read.c",O_RDWR);
	if(fd!=-1){
		printf("file opened");
		write(fd,wr,sizeof(wr));
		lseek(fd,0,SEEK_SET);
		read(fd,rd,sizeof(rd));
		printf("\n file content is %s\n",rd);
	}
}

