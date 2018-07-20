#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
  int p; /* the number of MPI processes */
  int id; /* the rank of this process */
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);

#if 0
  if(p > 1) {
    char msgtosend[256];
    char msgtorecv[256];
    sprintf(msgtosend, "hello message from process %d", id);
    MPI_Send(msgtosend, strlen(msgtosend)+1, MPI_CHAR,
	     (id+1)%p, 0, MPI_COMM_WORLD);
    MPI_Recv(msgtorecv, 256, MPI_CHAR, MPI_ANY_SOURCE,
	     MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    printf("%d: received a message: \"%s\"\n", id, msgtorecv);
  }
#endif

  if(p > 1) {
    char buffer[256];
    if(!id) {
      sprintf(buffer, "hello message from process %d", id);
      MPI_Send(buffer, strlen(buffer)+1, MPI_CHAR,
	       (id+1)%p, 0, MPI_COMM_WORLD);
    }

    int i;
    for( i = 0; i < 10; i++) {
      MPI_Recv(buffer, 256, MPI_CHAR, MPI_ANY_SOURCE,
	       MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      printf("%d: received a message: \"%s\"\n", id, buffer); fflush(0);
      MPI_Send(buffer, strlen(buffer)+1, MPI_CHAR,
	       (id+1)%p, 0, MPI_COMM_WORLD);
    }
  }

  MPI_Finalize();
  return 0;
}
