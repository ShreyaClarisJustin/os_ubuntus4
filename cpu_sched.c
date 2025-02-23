#include<stdio.h>
#include<stdlib.h>
struct process
{
	int pid,arr_t,burst_t,pri,resp_t,start_t,comp_t,turn_t,wait_t,completed,remain,rbt,flag,et;
	struct process *next;
	struct process *prev;
};
typedef struct process node;
node *head1,*head2;
int n,p=0,time=0,quantum=1,total_burst=0;
float avg_resp=0,avg_comp=0,avg_turn=0,avg_wait=0;
void create(){
	int i;
	int total_burst;
	node *temp,t1,temp2;
	temp=head;
	printf("enter the no of processes");
	scanf("%d",&n);
	p=n;
	for(i=0;i<n;i++){
		printf("enter pid,arr_t,burst_t,prio");
		if(i==0){
			temp=(node *)malloc(sizeof(node));
			scanf("%d%d%d%d",&temp->pid,&temp->arr_t,&temp->burst_t,&temp->pri);
			if(i==0||i==n-1){
				tot_burst+=temp->arr_t;
				tot_burst+=temp->burst_t;
			}
			head1=temp;
			temp2=head;
		}
		else{
			t1=temp;
			 temp=(node *)malloc(sizeof(node));
			scanf("%d%d%d%d",&temp->pid,&temp->arr_t,&temp->burst_t,&temp->pri);
                        if(i==0||i==n-1){
                                tot_burst+=temp->arr_t;
                                tot_burst+=temp->burst_t;
                        }
			temp2->next=temp;
			
		}
	}
}
void main(){
}
