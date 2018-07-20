#include "mpi.h"
#include <math.h>

int main (int argc, char ** argv[]) {

  int done = 0, n, myid, numprocs, i, rc;
  double PI25DT = 3.141592653589793238462643;
  double mypi, pi, h, sum, x, a;

  /*  MPI_Init always takes &argc and &argv and looks for
      MPI specific arguements like -np <num processors> */
  MPI_Init(&argc,&argv);

  /* this says how processes are running - related to
     the -np ; if don't specify then just get 1  */
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

  /* each process 0 to <numprocesses -1> gets a unique id */
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);

  printf("this is node %d of %d total\n", myid, numprocs);

  while (!done)
    {
      /* only process 0 asks the user for input */
      if (myid == 0) {
	printf("Enter the number of intervals: (0 quits)\n ");
	scanf("%d",&n);
      }

      /* process 0 sends the value of n to all other processes */
      MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

      /* if user entered 0 then break */
      if (n == 0) break;

      /* each process takes a different portion of the calculation */
      h = 1.0 / (double) n;
      sum = 0.0;

      /* Example if n is 10 and numprocs is 5:
         0 will take 1,6
         1 will take 2,7
	 2 will take 3,8
	 4 will take 4,9
	 5 will take 5,10
	 */
      for (i = myid + 1; i <= n; i += numprocs) {
	x = h * ((double)i - 0.5);
	sum += 4.0 / (1.0 + x*x);
      }

      mypi = h * sum;

      printf("node %d: local pi value is %.16f\n", myid, mypi);

      /* this sums together every processes mypi variable and
         puts it into the the pi variable */
      MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

      /* only process 0 prints it out */
      if (myid == 0)
	printf("pi is approximately %.16f, Error is %.16f\n",
	       pi, fabs(pi - PI25DT));

    }

    MPI_Finalize();
}
