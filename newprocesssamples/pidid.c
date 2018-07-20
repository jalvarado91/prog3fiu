#include <sys/types.h>
#include <stdio.h>

int main()
{
   pid_t pid, ppid;
   printf("My PID is: %d\n\n",(pid = getpid()));
   printf("Par PID is: %d\n\n",(ppid = getppid()));

   return(0);
   // exit(0);
}
