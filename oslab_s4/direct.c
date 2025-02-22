#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
int main()
{
   DIR *d;
   struct dirent *de;
   struct stat f;
   int value;
   d=opendir(".");
   if(d==NULL)
   {
      printf("Could not open");
   }
   de=readdir(d);
   while(de!=NULL)
   {
      value=stat(de->d_name,&f);
      if(value<0)
      {
         printf("Couldn't find file");
      }
      else
      {
         printf("%s %ld\n",de->d_name,f.st_size);
      }
      de=readdir(d);
   }
   closedir(d);
}
