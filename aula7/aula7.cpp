#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "mpi.h"

#define TAM 8

void gerarVet(int vet[TAM]);

int main()
{
	int rank, size, soma_p = 0, soma_tot = 0;
	int tam;

	
	int Vet[TAM];
	MPI_Status stat;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	tam = TAM/size;
	int subVet[tam];

	if(rank == 0)
		gerarVet(Vet);

	MPI_Scatter(Vet, tam, MPI_INT, subVet, tam, MPI_INT, 0, MPI_COMM_WORLD);

	for(int i = 0; i< tam; i++)
		soma_p += subVet[i];

	if (rank == 0)
	{
		soma_tot = soma_p;
		for(int i = 1; i< size; i++){
			MPI_Recv(&soma_p, 1, MPI_INT, i, 500, MPI_COMM_WORLD, &stat);
			soma_tot += soma_p;
		}
		printf("Soma total = %d \n",soma_tot );
	}

	else

		MPI_Send(&soma_p, 1, MPI_INT, 0, 500, MPI_COMM_WORLD);

	MPI_Finalize();
	return 0;
}

void gerarVet(int vet[TAM]){
	srand(time(NULL));
	for(int i = 0; i < TAM; i++)
	{
		vet[i] = rand()%10;
		printf("V[%d] = %d\n", i, vet[i]);
	}
}


