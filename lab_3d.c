#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
void main(){
	int fd;
	char buff[50];
	char msg[50]="HELLO";
	fd=open("f1.txt",O_RDWR|O_CREAT,0744);
	printf("value of fd is%d\n",fd);
	if(fd!=-1){
		printf("file opened");
                write(fd,msg,sizeof(msg));
                lseek(fd,0,SEEK_SET);
                read(fd,buff,strlen(msg));
                printf("%sis written",buff);
                close(fd);
	}
}
