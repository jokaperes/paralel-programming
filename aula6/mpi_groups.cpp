#include <stdio.h>
#include "mpi.h"

#define NPROCS 8


int main(int argc,char* argv[]){
	int ranks1[4] = {0, 1, 2, 3}, ranks2[4] = {4, 5, 6, 7};
	int rank, size, sendbuf, recvbuf, new_rank;

	MPI_Group orig_group, new_group;
	MPI_Comm new_comm;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	sendbuf = rank;

	MPI_Comm_group(MPI_COMM_WORLD, &orig_group);

	if(rank < NPROCS/2)
		MPI_Group_incl(orig_group, NPROCS/2, ranks1, &new_group);
	else	
		MPI_Group_incl(orig_group, NPROCS/2, ranks2, &new_group);

	MPI_Comm_create(MPI_COMM_WORLD, new_group, &new_comm);

	MPI_Allreduce(&sendbuf, &recvbuf, 1, MPI_INT, MPI_SUM, new_comm);

	MPI_Group_rank(new_group, &new_rank);

	printf("rank = %d, novo_rank = %d, recvbuf = %d. \n",rank, new_rank, recvbuf);
	MPI_Finalize();
	return 0;



}