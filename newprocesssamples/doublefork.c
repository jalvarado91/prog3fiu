#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
      if (fork() ==0)
      {
         /*child */
         execlp( "./sleepy", "./sleepy", (char *) 0);
         printf("execlp failed\n");
         exit(1);
      }
      else
      {
         if (fork() ==0)
         {
            execlp("./sleepy2","./sleepy2", (char *) 0);
            printf("execlp failed\n");
            exit(1);
         } 
         else
         {
            sleep(7);
            printf("parent done\n");
         }
      }
}

