#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char *ls_cmd = "ls";
char *sort_cmd = "sort";

void runsource(int pipefd[]);
void rundest(int pipefd[]);

int
main(int argc, char **argv)
{
	int pipefd[2];
	int pid, status, ls_pid, sort_pid;

	pipe(pipefd);

	if ((ls_pid = fork()) == 0) {
		dup2(pipefd[1], 1); // To stdout
		close(pipefd[0]); 
		execlp(ls_cmd, ls_cmd, NULL); // Run ls
		perror(ls_cmd);
	}
	
	if ((sort_pid = fork()) == 0) {
		dup2(pipefd[0], 0);	// stdin
		close(pipefd[1]);	
		execlp(sort_cmd, sort_cmd, NULL);	// Run sort
		perror(sort_cmd);	
	}
	
	close(pipefd[0]); 
	close(pipefd[1]);

	wait(&status);
	wait(&status);
	exit(0);
}