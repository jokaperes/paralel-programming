#include <stdio.h>
#include "mpi.h"


#define VALOR 128

int main(){
	int size, rank;
	int valor;
	MPI_Status status;

	


	 MPI_Init(NULL, NULL);
	 MPI_Comm_size(MPI_COMM_WORLD, &size);
	 MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	 if(rank == 0){
	 	valor = 128;
	 	for(int i = 1; i < size; i++){
	 		MPI_Send(&valor, 1 ,MPI_INT, i, 0, MPI_COMM_WORLD);
	 	}
	 }
	 else{
	 	MPI_Recv(&valor, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
	 	printf("\nProcesso %2d de %2d processos. Valor recebido: %2d.\n", rank, size, valor);

	 }

	 MPI_Finalize();







	return 0;



}

