#include <unistd.h>	/* defines fork(), and pid_t.      */
#include <sys/wait.h>	/* defines the wait() system call. */
#include <stdio.h>

int main()
{
   /* storage place for the pid of the child process, and its exit status. */
   pid_t child_pid;
   int child_status;

   /* lets fork off a child process... */
   child_pid = fork();

   /* check what the fork() call actually did */
   int i,k;
   switch (child_pid)
   {
      case -1:	/* fork() failed */
    	perror("fork");	/* print a system-defined error message */
    	return(1);
      case 0:	/* fork() succeeded, we're inside the child process */
        for(i=1;i<50;i++)
        {
           sleep(2);
           printf("hello world\n");
        }
        return(0);	/* here the CHILD process exits, not the parent. */
      default:	/* fork() succeeded, we're inside the parent process */
        for (k=1;k<10;k++)
        {
           sleep(1);
           printf("parent running\n");
        }
        wait(&child_status);
        printf("Child finished\n");	/* wait till the child process exits */
   }

   int j;
   for (j=1;j<100;j++)
   {
	   sleep(2);
	   printf("testing\n");
   }
   return(0);
}
