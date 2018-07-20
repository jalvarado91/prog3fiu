#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{

  int i;

   for(i=0; i<20; i++)
   {
      printf("In second sleepy %d : %d\n",getpid(), getppid());
      sleep(2);
   } 

}

