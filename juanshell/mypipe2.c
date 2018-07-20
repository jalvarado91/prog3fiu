#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include<fcntl.h>
#include<string.h>
#define MAX_ARGS 20
#define BUFSIZ 1024

int get_args(char* cmdline, char* args[])
{
  int i=0;
  char* arg;
  
/* if no args */
if((args[0] = strtok(cmdline, "\n\t ")) == NULL)
return 0;
while((args[++i] = strtok(NULL, "\n\t ")) != NULL) {
  
 if(i >= MAX_ARGS) {
printf("Too many arguments!\n");
exit(1);
}
 }

 

/* the last one is always NULL */

return i;
}
void execute(char* cmdline) 
{
  int pid,async,status;
  int i=0 ,j=0,l=0,k=0,fd,pipeamt=0,pipearrsz=0;
  char* args[MAX_ARGS];
  int offset[MAX_ARGS];
 
char* outfile = NULL;
char* append = NULL;
char* infile = NULL; 
 int redirect = 0;
  char* pipeargs[MAX_ARGS] = {0};
  int nargs = get_args(cmdline, args);
  pipeargs[0] = args[0];
  pipearrsz++;
  if(nargs <= 0) return;

  if(!strcmp(args[0], "quit") || !strcmp(args[0], "exit")) {
    exit(0);
  }

  /* check if async call */
  if(!strcmp(args[nargs-1], "&")) { async = 1; args[--nargs] = 0; }
  else async = 0;

  while(args[i] != NULL){
   
    if(!strcmp(args[i],"|")){
      if(args[i+1] == NULL){
	perror("Missing pipe dest");
	  return;}
      args[i] = NULL;
      pipeargs[++j] = args[i+1];
      offset[l++] = i+1;
      pipeamt++;
      pipearrsz++;
     
    }
    i++;
  }


  int pipefd[2*pipeamt];
   for(i = 0; i < pipeamt; i++){
        if(pipe(pipefd + i*2) < 0) {
            perror("Pipe failed");
            exit(1);
        }
    }

   
  
 k = 0;
 l = 0;
 j = 0;
  for(i=0;i<pipearrsz;i++){
	   int pid2;
	   printf("size%d",pipearrsz);
	
      	pid2 = fork();
	if(pid2 < 0) { /* an error occurred */
	perror("fork failed");
	exit(-1);
	} else if(pid2 == 0) { /* child process */
	 
 outfile = NULL;
 append = NULL;
 infile = NULL;
 redirect = 0;
while(args[k] != NULL)
   {
     printf("argsktest:%s\n",args[k]);
 if(!strcmp(">",args[k]) || !strcmp(">>",args[k]))
    {
      redirect = 1;
      if(!strcmp(">",args[k])){
      if(args[k-1] == NULL || args[k+1] == NULL){
	perror("Missing needed argument for redirection");
	return;
      }
      printf("i made it in\n");
     
       outfile = args[k+1];
       args[k] = NULL;
     
      }
    
else {
  
 if(args[k-1] == NULL || args[k+1] == NULL){
	perror("Missing needed argument for redirection");
	return;
      }
      printf("i made it in too\n");
     
      append = args[k+1];
      args[k] = NULL;
    
 }
    }
else if(!strcmp("<",args[k])){
  
 if(args[k-1] == NULL || args[k+1] == NULL){
	perror("Missing needed argument for redirection");
	return;
      }
      printf("i made it in too\n");
     
      infile  = args[k+1];
      args[k] = NULL;
      printf("infile:%s\n",infile);
 }
 k++;
   }
 k=0;
 while(args[k]!=NULL){
   printf("nargs[k]:%s\n", args[k]);
   k++;
 }


 if (i ==0 && infile){
 fd = 0;
 fd = open(infile,O_RDWR);
   
  
     if(fd<0){
	  perror(infile);
	  exit(1);
           }
	else{
	  dup2(fd,0);
	  close(fd);
	 
	}
 }
 
 if (pipeargs[i+1] == NULL && redirect)
   {
     if(outfile){
     fd =0;
    fd = open(outfile,O_CREAT|O_RDWR|O_TRUNC);
   
   
 if(fd<0){
	  perror(outfile);
	  exit(1);
           }
	else{
	  dup2(fd,1);
	  close(fd);
	}
     }
	
   
     else {
  
   fd = open(append,O_CREAT|O_RDWR|O_APPEND);
  
    if(fd<0){
	  perror(outfile);
	  exit(1);
           }
	else{
	  dup2(fd,1);
	  close(fd);
	 
	}
     }	 
   }
	
  if(pipeargs[i+1] != NULL){
	   
	
	     if(dup2(pipefd[j + 1], 1) < 0){
                    perror("dup2");
                    exit(EXIT_FAILURE);
	     }

	  }


 if(j != 0 ){
                if(dup2(pipefd[j-2], 0) < 0){
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            int c;
            for(c = 0; c < 2*pipeamt; c++){
                    close(pipefd[c]);
            }

	    fd = 0;     
	    /*
	    if(i==0){//if first iteration, do first command
	      if( execvp(args[0], args) < 0 ){
                    perror("exec failed");
                    exit(-1);
            }
	    }
	    else
	      if(execvp(args[offset[l-1]], args) < 0 ){
                    perror("exec failed");
                    exit(-1);
            }
	    */
	}
	int e  = 0;
	while(args[e] != NULL){
	  printf("e:%s\n",args[e]);
	  e++;
	}
 j+=2;
 k = offset[l];
 l++;
 
 
 for(i = 0; i < 2 * pipeamt; i++){
        close(pipefd[i]);
    }

    for(i = 0; i < pipeamt + 1; i++){
        wait(&status);
    }

}

}
 	
int main (int argc, char* argv [])
{
  char cmdline[BUFSIZ];
  
  for(;;) {
    printf("COP4338$ ");
    if(fgets(cmdline, BUFSIZ, stdin) == NULL) {
      perror("fgets failed");
      exit(1);
    }
    execute(cmdline) ;
  }
  return 0;
}
