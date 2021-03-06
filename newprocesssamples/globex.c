#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int globvar = 6;
char buf[] = "stdout write\n";

int main(void)
	{
  	int w = 88;
  	pid_t pid;
	  	write( 1, buf, sizeof(buf)-1 );
  	printf( "Before fork()\n" );

  	if( (pid = fork()) == 0 )
			{  /* child */
    	globvar++;
			w++;
  		}
  	else if( pid > 0 )       /* parent */
    	sleep(2);
  	else
    	perror( "fork error" );

  	printf( "pid = %d, globvar = %d, w = %d\n",
				getpid(), globvar, w );
  	return 0;
	} /* end main */


#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
void printpos(char *msg, int fd);
void fatal(char *msg);

int main(void)
{ int fd;		/* file descriptor */
  pid_t pid;
  char buf[10];	/* for file data */
   if ((fd=open("data-file", O_RDONLY)) < 0)
		perror("open");

  	read(fd, buf, 10);  /* move R-W ptr */

  	printpos( "Before fork", fd );

  	if( (pid = fork()) == 0 )
			{  /* child */
    	printpos( "Child before read", fd );
    	read( fd, buf, 10 );
    	printpos( " Child after read", fd );
  		}
		else if( pid > 0 )
		{    /* parent */
	wait((int *)0);
 	printpos( "Parent after wait", fd );
  	}
	else
		perror( "fork" );
}
void printpos( char *msg, int fd )
/* Print position in file */
	{
  	long int pos;

  	if( (pos = lseek( fd, 0L, SEEK_CUR) ) < 0L )
    	perror("lseek");

  	printf( "%s: %ld\n", msg, pos );
	}

