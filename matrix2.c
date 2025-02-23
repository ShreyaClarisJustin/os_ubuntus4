#include<stdio.h>//lakshmi gp
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<unistd.h>
typedef struct
{
        int m,n,status,A[10][10],T[10][10];
}node;

node *pt;

void main()
{
        int a=1,i,j,fd,siz=4096;
        char c[10] = "Absa";
        fd=shm_open("ca",O_CREAT|O_RDWR,0666);
        ftruncate(fd,sizeof(int));
        pt=(node*)mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
        printf("The matrix is: ");
        while(a==1)
        {
                //printf("The matrix is: ");
                if(pt->status==1)
                {
                        for(i=0;i<pt->n;i++)
                        {
                                printf("\n");
                                for(j=0;j<pt->m;j++)
                                printf(" %d ",pt->A[i][j]);
                        }pt->status=2;
                }
                if(pt->status==2)
                {
                       for(i=0;i<pt->m;i++)
                       		for(j=0;j<pt->n;j++)
                        		pt->T[i][j]=pt->A[j][i];
                        pt->status=3;
                }
               if(pt->status==4)
                {
                        a=0;
                }
        }
}
