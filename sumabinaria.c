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
		printf("por favor especifique el numero\n");
		exit(1);
	}
  sscanf(argv[1], "%i", &potencia);
  int poten = pot(2,potencia);
  //int * A = (int*) malloc ((poten/2)*sizeof(int));
  //int * B = (int*) malloc ((poten/2)*sizeof(int));
  //int * C = (int*) malloc ((poten/2)*sizeof(int));
  //int * D = (int*) malloc ((poten/2)*sizeof(int));
	int tam = poten/2;
  int An[tam];
  int Bn[tam];
  int Cn[tam];
  int Dn[tam];
  srand(time(NULL));

  for (int i=0 ;i <poten; i++)
  {
    Cn[i] = 0;
    Dn[i] = 0;
  }


  for (int i=0 ;i < poten; i++)
  {
    An[i] = 0 + rand() % (2);
    Bn[i] = 0 + rand() % (2);
    //printf("%i\n",A[i]);
  }
//void suma_acarreo(){
  int idHilo;
  omp_set_num_threads(poten);
  #pragma omp parallel shared(idHilo)
  {
    idHilo = omp_get_thread_num();

    if ((An[idHilo] == 1 )&&(Bn[idHilo]==1)){
      Cn[idHilo]=0;
      Dn[idHilo-1] =1;
    }else{
      Cn[idHilo] = An[idHilo] + Bn[idHilo];
    }
  }

//}


void recursion(){
  int idHilo;
  omp_set_num_threads(poten);
  #pragma omp parallel shared(idHilo)
  {
    idHilo = omp_get_thread_num();

    if ((Cn[idHilo] == 1 )&&(Dn[idHilo+1]==1)){
      Dn[idHilo-1] = 0;
      Cn[idHilo]=0;
    }else{
      Cn[idHilo] = Cn[idHilo] + Dn[idHilo+1];
    }
  }
}

void suma_acarreo(){
  int aux = 0;
  for(int i = 0; i < poten/2; i++){
    if(Dn[i] == 1){
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
  printf("%i",An[i]);
}
printf("\n");
for (int i=0 ;i <poten; i++)
{
  //A[i] = 0 + rand() % (2);
  //B[i] = 0 + rand() % (2);
  printf("%i",Bn[i]);
}
printf("\n");
printf("Arrgeglo Resultado: \n");
for (int i=0 ;i < poten; i++)
{
  //A[i] = 0 + rand() % (2);
  //B[i] = 0 + rand() % (2);
  printf("%i",Cn[i]);
}
printf("\n");
printf("Arrgeglo Aux: \n");
for (int i=0 ;i <poten; i++)
{
  //A[i] = 0 + rand() % (2);
  //B[i] = 0 + rand() % (2);
  printf("%i",Dn[i]);
}
printf("\n");
	return 0;
}
