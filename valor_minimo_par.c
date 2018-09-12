#include <omp.h>
#include <stdio.h>


	
#define N 450000000		// numero de iteracoes
int A[N], min;


int main(int argc, char const *argv[])
{

	omp_set_num_threads(1024);

	#pragma omp parallel for
	for (int i = 0; i < N; i++) {
	    A[i] = (N - 1) - i;
//	    A[i] = rand() % 10000;
	}



	/*for (int j = 0; j < N; j++)
	{
		printf("Posicao A[%d] - %d\n", j, A[j]);
	}*/


	int min = A[0]; 
	//printf("valor de min = %d\n", min);
	//printf("valor de A[0] = %d\n", A[0]);
	
	int troca = 0;

	#pragma omp parallel reduction (+:troca)
	{
		int id = omp_get_thread_num();
		#pragma omp for
		for (int i = 1; i< N; i++) {
		    if (A[i] < min) {
		    	troca = troca+1;
				min = A[i]; 
			}
		}
	}


	printf("min = %d, N = %d SEQ / numero de trocas = %d \n", min, N, troca);




	return 0;
}