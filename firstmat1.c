#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main(){
	
	int i,j,m,n;
	int m1[5][5],res[5][5];
	int fd=shm_open("mat",O_CREAT|O_RDWR,0666);
	int * matrix=(int *)mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	printf("enter no of rows of a");
	scanf("%d",&m);
	printf("enter the no of columns of a");
	scanf("%d",&n);
	int size=m*n;
	memcpy(&matrix,m1,sizeof(int));
	printf("enter the elelments of first matrix");
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			scanf("%d",&m1[i][j]);
		}
	}
	printf("waiting for the second matrix elements to be entered\n");
	sleep(5);
	munmap("matrix",10*sizeof(int));
	close(fd);
}
