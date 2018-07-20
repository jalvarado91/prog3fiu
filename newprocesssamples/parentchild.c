#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
   pid_t pid;         /* could be int */
   int i;

   pid = fork();
   if( pid > 0 )
   {
      /* parent */
      for( i=0; i < 1000; i++ )
         printf("\t\t\tPARENT %d\n", i);
   }
   else
   {
      /* child */
      for( i=0; i < 1000; i++ )
         printf( "CHILD %d\n", i );
   }
   return (0);
}

