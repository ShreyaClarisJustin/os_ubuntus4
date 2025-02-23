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
        int fd,siz=4096,i,j,a=1;
        char c[10] = "Absa";
        fd=shm_open("ca",O_CREAT|O_RDWR,0666);
        ftruncate(fd,sizeof(int));
        pt=(node*)mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
        pt->status=0;
        while(a==1)
        {
                if(pt->status==0)
                {
                        printf("Enter the dimensions");
                        scanf("%d%d",&pt->n,&pt->m);
                        printf("Enter the matrix");
                        for(i=0;i<pt->n;i++)
                        	for(j=0;j<pt->m;j++)
                        		scanf("%d",&pt->A[i][j]);
                       /* for(i=0;i<pt->n;i++)
                        {
                                printf("\n");
                                for(j=0;j<pt->m;j++)
                                printf(" %d ",pt->A[i][j]);
                        }*/
                        pt->status=1;
                }
                if(pt->status==3)
                {
                        printf("\n The transpose of the matris is");
                        for(i=0;i<pt->m;i++)
                        {
                                printf("\n");
                                for(j=0;j<pt->n;j++)
                                {	printf(" %d ",pt->T[i][j]);
				}
                        }
			pt->status=4;
                }
                if(pt->status==4)
                {
                        a=0;
                }
        }
}

