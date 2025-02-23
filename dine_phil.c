#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>
#include<stdlib.h>
#include<semaphore.h>
#include<sys/types.h>

sem_t s[5];//5 chopsticks
int p[5];
pthread_t thread[5];

void eat(int);

void *philo(void *n)
{
  int ph=*(int *)n;
  printf("Philospher %d Came to eat\n",ph);
  sem_wait(&s[ph]);
  printf("Philospher %d take left stick\n",ph);
  sem_wait(&s[(ph+1)%5]);
  printf("Philospher %d take right stick\n",ph);
  eat(ph);
  sleep(2);
  printf("Philospher %d is Finished\n",ph);
  sem_post(&s[(ph+1)%5]);
  printf("Philospher %d released the right stick\n",ph);
  sem_post(&s[ph]);
  printf("Philospher %d released the left stick\n",ph);
}
void eat(int ph)
{
  printf("Philospher %d Started\n",ph);
}

int main(){
  	int i;
  	for(i=0;i<5;i++)
    		sem_init(&s[i],0,1);
  	for(i=0;i<5;i++)
   	{
     		p[i]=i;//if i=0 it mean that philosopher is passed into that fn
     		pthread_create(&thread[i],NULL,philo,(void *)&p[i]);
   	} 
  	for(i=0;i<5;i++)
    		pthread_join(thread[i],NULL); 
}
