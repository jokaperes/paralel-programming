	#include <stdio.h>
	#include "mpi.h"
	#include <stdlib.h>

	int main(){
		int rank, size;

		MPI_Init(NULL, NULL);
		MPI_Comm_size(MPI_COMM_WORLD, &size);
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		if(rank != 0){
			int source = ((rank + 1) % 10) *100;
			MPI_Send(&source, 4, MPI_BYTE, 0, 5, MPI_COMM_WORLD);
		}
		else{
			int dest;
			for(int i = 1; i < size; i ++){
				MPI_Recv(&dest, 4, MPI_BYTE, i, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				printf("\nRecebido de %2d o valor %2d \n",i, dest );
			}
		}

	MPI_Finalize();
	return 0;
	}
	
