#include <stdio.h>
#include <stdlib.h>
#include<mpi.h>

// mpirun -n 5 ./mpi.e
//  mpicc mpi.c -o mpi.e

int main(int argc, char *argv[])
{
	int size, myRank;
	MPI_Status st;

	int valorInicial, valorModificado, total, nproc;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size); //comunicador MPI_COMM_WORLD qtos processos o usuario mandou disparar
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

	printf("Processo %d de %d \n", myRank, size);
	fflush(stdout);

	if (myRank ==0){
		for (nproc=1; nproc < size; nproc++)
		{
			valorInicial = nproc*10;
			MPI_Send(&valorInicial,1, MPI_INT, nproc, 0, MPI_COMM_WORLD);
			printf("Mestre - Enviei %d para o PROC %d  \n", valorInicial, nproc);
			fflush(stdout);

		}

		for (nproc = 1; nproc < size; nproc++)
		{
			//MPI_Recv(&valorModificado, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &st);
			MPI_Recv(&valorModificado, 1, MPI_INT, nproc, 1, MPI_COMM_WORLD, &st);
			printf("Mestre recebeu %d - Escravo %d \n", valorModificado,nproc);
			fflush(stdout);

			total+=valorModificado;
		}

		printf("Total do processamento = %d\n", total);
		fflush(stdout);

	}else{
		MPI_Recv(&valorInicial, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);
		printf("Escravo %d - Recebi %d \n", myRank, valorInicial);
		fflush(stdout);
		valorModificado = valorInicial *10;

		MPI_Send(&valorModificado, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		printf("Esvravo %d - Enviou %d \n", myRank, valorModificado);
		fflush(stdout);
	}


	



	MPI_Finalize();



	return 0;
}