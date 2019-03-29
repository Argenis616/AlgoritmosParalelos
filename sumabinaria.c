#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>



int pot( int base, int exp)
{
	if(exp == 0)
	{
		return 1;
	} else
	{
		return base*pot(base, exp-1);
  }
}

int main(int argc, char **argv)
{
	int potencia;

  if (argc < 2)
  {
		printf("por favor especifique dos numeros vertice y la semilla\n");
		exit(1);
	}
  sscanf(argv[1], "%i", &potencia);
  int poten = pot(2,potencia);
  int * A = (int*) malloc ((poten/2)*sizeof(int));
  int * B = (int*) malloc ((poten/2)*sizeof(int));
  int * C = (int*) malloc ((poten/2)*sizeof(int));
  int * D = (int*) malloc ((poten/2)*sizeof(int));
  A[poten/2] = 0;
  B[poten/2] = 0;
  C[poten/2] = 0;
  D[poten/2] = 0;
  int arreglo[poten];
  srand(time(NULL));

  for (int i=0 ;i <poten; i++)
  {
    C[i] = 0;
    D[i] = 0;
  }


  for (int i=0 ;i <poten; i++)
  {
    A[i] = 0 + rand() % (2);
    B[i] = 0 + rand() % (2);
    printf("%i\n",A[i]);
  }
//void suma_acarreo(){
  int idHilo;
  omp_set_num_threads(poten);
  #pragma omp parallel shared(idHilo)
  {
    idHilo = omp_get_thread_num();

    if ((A[idHilo] == 1 )&&(B[idHilo]==1)){
      C[idHilo]=0;
      D[idHilo-1] =1;
    }else{
      C[idHilo] = A[idHilo] + B[idHilo];
    }
  }

//}


void recursion(){
  int idHilo;
  omp_set_num_threads(poten);
  #pragma omp parallel shared(idHilo)
  {
    idHilo = omp_get_thread_num();

    if ((C[idHilo] == 1 )&&(D[idHilo+1]==1)){
      D[idHilo-1] = 0;
      C[idHilo]=0;
    }else{
      C[idHilo] = C[idHilo] + D[idHilo+1];
    }
  }
}

void suma_acarreo(){
  int aux = 0;
  for(int i = 0; i < poten/2; i++){
    if(D[i] == 1){
      aux = 1;
    }
  }

  if(aux == 1){
      recursion();

  }


}

suma_acarreo();

for (int i=0 ;i <poten; i++)
{
  //A[i] = 0 + rand() % (2);
  //B[i] = 0 + rand() % (2);
  printf("%i",A[i]);
}
printf("\n");
for (int i=0 ;i <poten; i++)
{
  //A[i] = 0 + rand() % (2);
  //B[i] = 0 + rand() % (2);
  printf("%i",B[i]);
}
printf("\n");
for (int i=0 ;i < poten; i++)
{
  //A[i] = 0 + rand() % (2);
  //B[i] = 0 + rand() % (2);
  printf("%i",C[i]);
}
printf("\n");
for (int i=0 ;i <poten; i++)
{
  //A[i] = 0 + rand() % (2);
  //B[i] = 0 + rand() % (2);
  printf("%i",D[i]);
}
printf("\n");
	return 0;
}
