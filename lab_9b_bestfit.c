#include<stdio.h>
void main(){
        int choice;
        int tot_no_blk,tot_no_proc;
        int blk_space[20],proc_space[20];
        printf("enter the no of blocks of memory");
        scanf("%d",&tot_no_blk);
        printf("enter the size of each block");
        for(int i=0;i<tot_no_blk;i++){
                scanf("%d",&blk_space[i]);
        }
        printf("enter the no of processes");
        scanf("%d",&tot_no_proc);
        printf("enter the size of each process");
        for(int i=0;i<tot_no_proc;i++){
                scanf("%d",&proc_space[i]);
        }
         int alloc[20];
        for(int i=0;i<tot_no_blk;i++){
                alloc[i]=-1;
        }


	for(int i=0;i<tot_no_proc;i++){
        	int bestidx=-1;
                for(int j=0;j<tot_no_blk;j++){

                        if(proc_space[i]<=blk_space[j]){

                                if(bestidx==-1){
                                        bestidx=j;
                                }
                                else{
                                        if(blk_space[bestidx]>blk_space[j])
                                        {
                                                bestidx=j;
                                        }
                                }
                        }
                }
                if(bestidx!=-1){
                        alloc[i]=bestidx;
                        blk_space[bestidx]=blk_space[bestidx]-proc_space[i];
                }
        }
	printf("\nProcess No.\tProcess Size\tallocatedBlock no.\tsize_of_blk\n");
        for (int i = 0; i <tot_no_proc; i++)
        {
                printf(" %i\t\t", i+1);
                printf("%i\t\t", proc_space[i]);
                if (alloc[i] != -1)
                        printf("%d\t\t\t%d", alloc[i] + 1,blk_space[alloc[i]]);
                else
                        printf("Not Allocated");
                printf("\n");
        }
}

