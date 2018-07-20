#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  pid_t pid;

  pid = fork();
  if(pid < 0) { /* an error occurred */
    perror("fork failed");
    exit(-1);
  } else if(pid == 0) { /* child process */
    printf("I AM THE CHILD PROCESS... sleeping for 30 seconds\n");
    sleep(30);
    printf("CHILD FINISHES\n");
  } else { /* parent process */
    printf("I AM THE PARENT PROCESS... sleeping for 60 seconds\n");
    sleep(60);
    printf("PARENT FINISHES\n");
  }
  return 0;
}
