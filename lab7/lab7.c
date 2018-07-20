/*
	Author:			Juan Alvarado
	Panther ID:		3367805
	Description:	Write a C program that passes an array of doubles through 
					a set of processes
	Originality:	I affirm that this program is entirely my own work and 
			none of it is the work of any other person
*/

#include <stdio.h>
#include <mpi.h>

#define NUMITEMS 10000

double nums[NUMITEMS];

int main (int argc, char *argv[]) {
	MPI_Status status;
   
	int processes;
  	int p_rank;
  	double elapsed_time;

 	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &processes);
	MPI_Comm_rank(MPI_COMM_WORLD, &p_rank);

	MPI_Barrier(MPI_COMM_WORLD);
  	elapsed_time = - MPI_Wtime();
	
	if (!p_rank) { // Root Process
		// init array
		int i = 0;
  		for (; i < NUMITEMS; i++) {
			nums[i] = i;  
  		}
		
		MPI_Send(&nums, NUMITEMS, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(&nums, NUMITEMS, MPI_DOUBLE, processes - 1, 0, MPI_COMM_WORLD, &status);
	} 
	else {
		MPI_Recv(&nums, NUMITEMS, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		MPI_Send(&nums, NUMITEMS, MPI_DOUBLE, (p_rank+1)%processes, 0, MPI_COMM_WORLD);	
	}

	MPI_Barrier(MPI_COMM_WORLD);
	elapsed_time += MPI_Wtime();

	if (!p_rank) // Root prints elapsed time
		printf("Execution time %8.6f\n", elapsed_time);
	
	MPI_Finalize();
	return 0;
}
