all:	circuit complex-mpi-pi helloworld sendrecv seqcircuit simple-mpi-pi pi mpi_hello

circuit:	circuit.c
		/usr/lib64/openmpi/bin/mpicc -O -o circuit circuit.c

complex-mpi-pi: complex-mpi-pi.c
		/usr/lib64/openmpi/bin/mpicc -O -o complex-mpi-pi complex-mpi-pi.c

helloworld: helloworld.c
		/usr/lib64/openmpi/bin/mpicc -O -o helloworld helloworld.c

sendrecv: sendrecv.c
		/usr/lib64/openmpi/bin/mpicc -O -o sendrecv sendrecv.c

seqcircuit: seqcircuit.c
		/usr/lib64/openmpi/bin/mpicc -O -o seqcircuit seqcircuit.c

simple-mpi-pi: simple-mpi-pi.c
		/usr/lib64/openmpi/bin/mpicc -O -o simple-mpi-pi simple-mpi-pi.c

pi: pi.c
	/usr/lib64/openmpi/bin/mpicc -O -o pi pi.c	

mpi_hello: mpi_hello.c
	/usr/lib64/openmpi/bin/mpicc -O -o mpi_hello mpi_hello.c

clean:
		rm -f circuit complex-mpi-pi helloworld sendrecv seqcircuit pi mpi_hello simple-mpi-pi core *~
