#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
   fork();//by this fork a child process is also created printing the same with different process IDs
   fork();
   fork();
   printf("Hello,I am Shreya!\n PID=%d\n",getpid());
   return 0;
}
