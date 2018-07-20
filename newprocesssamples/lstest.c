#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main ()
{
	int fileId;
	fileId = creat( "x.lis",0640 );
  if( fileId < 0 )  
  {  
	fprintf( stderr, "error creating x.lis\n" ); 
	exit (1);     
  }  

  dup2( fileId, fileno(stdout) ); /* copy fileID to stdout */
  close( fileId );     		
  execl( "/bin/ls", "ls", 0 );
}
