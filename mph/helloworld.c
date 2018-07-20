#include <stdio.h>
#include <mpi.h>
#include <unistd.h>

int x = 0;

int main(int argc, char* argv[])
{
  int p, id;
  char hostname[1024];

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);

  hostname[1023] = '\0';
  gethostname(hostname, 1023);
  printf("MPI size=%d, rank=%d on host %s\n", p, id, hostname);

  x = x+id;
  printf("x=%d id=%d\n", x,id);

  MPI_Finalize();
  return 0;
}
