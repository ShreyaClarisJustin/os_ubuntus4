#include<stdio.h>
void display(int tot_no_blk,int blk_space[],int tot_no_proc,int proc_space[],int alloc[]);
void firstfit(int tot_no_blk,int blk_space[],int tot_no_proc,int proc_space[],int alloc[]);
void bestfit(int tot_no_blk,int blk_space[],int tot_no_proc,int proc_space[],int alloc[]);

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

	while(1){
		printf("1.first fit\n2.best fit\n 3.worst fit\n4.display\n");
		printf("enter the choice");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				firstfit(tot_no_blk,blk_space,tot_no_proc,proc_space,alloc);
				break;
			case 2:
				bestfit(tot_no_blk,blk_space,tot_no_proc,proc_space,alloc);
				break;
			case 3:
				//worstfit(tot_no_blk,blk_space,tot_no_proc,proc_space,alloc);
				break;
			case 4:
				display(tot_no_blk,blk_space,tot_no_proc,proc_space,alloc);
				break;
		}

	}
}

void firstfit(int tot_no_blk,int blk_space[],int tot_no_proc,int proc_space[],int alloc[]){

	/*int alloc[20];
	for(int i=0;i<tot_no_blk;i++){
		alloc[i]=-1;
	}*/
	for(int i=0;i<tot_no_proc;i++){
		for(int j=0;j<tot_no_blk;j++){
			if(proc_space[i]<blk_space[j]){
				alloc[i]=j;
				blk_space[j]=blk_space[j]-proc_space[i];
				break;
			}
		}
	}
}
	/*printf("\nProcess No.\tProcess Size\tBlock no.\tproc_Size allocated\n");
    	for (int i = 0; i <tot_no_proc; i++)
    	{
        	printf(" %d\t", i+1);
        	printf("\t%d\t", proc_space[i]);
        	if (alloc[i] != -1)
            		printf("\t%d\t%d",alloc[i]+ 1,proc_space[alloc[i]]);
        	else
            	{	printf("Not Allocated");
        		//printf("\n");
		}
		printf("\n");
    	}
	*/
void display(int tot_no_blk,int blk_space[],int tot_no_proc,int proc_space[],int alloc[]){

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
void bestfit(int tot_no_blk,int blk_space[],int tot_no_proc,int proc_space[],int alloc[]){



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
}
