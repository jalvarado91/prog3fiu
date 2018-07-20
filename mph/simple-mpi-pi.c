#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int calc_darts(int n)
{
  int i, s = 0;
  for(i=0; i<n; i++) {
    double x = (double)rand()/RAND_MAX;
    double y = (double)rand()/RAND_MAX;
    if(sqrt(x*x+y*y) <= 1) s++;
  }
  return s;
}

int main(int argc, char* argv[])
{
  int p, id;
  int n; /* number of darts to throw for all processes */
  int s, t; /* number of darts landed in the pie here and everywhere */
  int seed; /* random seed to start with */

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);

  if(argc != 3) { 
    printf("USAGE: mpirun -np <p> %s <num_darts> <rand_seed>\n", argv[0]); 
    MPI_Finalize();
    return -1; 
  }
  n = atoi(argv[1]);
  seed = atoi(argv[2]+id);

  srand(seed); /* initialize rand seed */

  s = calc_darts(n/p);
  MPI_Reduce(&s, &t, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  if(!id) printf("pi =~ %lf\n", 4.0*t/n);

  MPI_Finalize();
  return 0;
}
