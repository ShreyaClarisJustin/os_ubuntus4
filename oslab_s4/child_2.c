#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/wait.h>
int main()

{
   int ret_value=fork();
   if(ret_value<0)
   {
      printf("failed");
   }
   else if(ret_value==0)
   {
      printf("This is child process with process id:%d and its parent process id:%d\n",getpid(),getppid());//in the child process ret_value is always zero,so for process id use getpid()
      exit(0);
   }
   else
   {
     wait(NULL);
      printf("This is the parent process with process id:%d and its child process id:%d\n",getpid(),ret_value);
      printf("The child process has exited\n");
      exit(0);
   }
}
