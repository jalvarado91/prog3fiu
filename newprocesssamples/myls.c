#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  pid_t pid;

  pid = fork();
  if(pid < 0) { /* an error occurred */
    perror("fork failed");
    exit(-1);
  } else if(pid == 0) { /* child process */
    printf("I AM A CHILD PROCESS\n");
    execlp("/bin/ls", "ls", "-l", NULL);
    /* return only when exec fails */
    perror("exec failed");
    exit(-1);
  } else { /* parent process */
    wait(0);
    printf("PARENT PROCESS FOUND CHILD PROCESS COMPLETED\n");
  }
  return 0;
}
