#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(int argc,char *argv[])
{
   int ret_value=fork();
   if(ret_value<0)
   {
      printf("Error");
   }
   else if(ret_value==0)
   {
      //printf("Child process");
      execlp("./add","add","1","2",NULL);
      exit(0);
   }
   else
   {
      wait(NULL);
      printf("Parent process\n");
      exit(0);
   }
}
