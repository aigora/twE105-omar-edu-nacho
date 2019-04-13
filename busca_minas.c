#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define D 20//dimensión de la matriz
void imprime_matriz(int M[D][D]);
void crear_buscaminas(int M[D][D]);//pone en cada casilla el número de bombas que tiene alrededor
int bombas_alrededor(int M[D][D],int i,int j);//cuenta el numero de bombas alrededor de una posición (i,j)
int main()
{
int random,bombas=0,Mapa[D][D]={0,0,0},fila,columna;
//Genera semilla aleatoria
srand(time(NULL));
//Numero aleatorio entre 1 y 100
for(fila=0;fila<D;fila++){
	for(columna=0;columna<D;columna++){
		random = rand() % 10 + 1;
		if(random<5){//Va recorriendo la matriz y generando números random, si son menores que 5 pone una bomba(-1) en esa posición
			Mapa[fila][columna]=-1;
			bombas++;
		}
	}
}
crear_buscaminas(Mapa);
imprime_matriz(Mapa);
printf("hay %i bombas",bombas);
return 0;
}
void imprime_matriz(int M[D][D]){
	int i,j;
	printf(" \t");
	for(i=0;i<D;i++){
		if(i<10)
			printf(" ");
		printf(" %i ",i);
	}
	printf("\n\n");
	for(i=0;i<D;i++){
		printf("%i\t",i);
		for(j=0;j<D;j++){
			if(M[i][j]>=0)//La matriz no va a tener un numero, mayor que 8 nunca
				printf(" ");//pone un espacio para que ocupe el mismo espacio que el -1 y se descuadre la matriz
			printf(" %i ",M[i][j]);
		}
		printf("\n");	
	}
}
void crear_buscaminas(int M[D][D]){
	int i,j;
	for(i=0;i<D;++i){
		for(j=0;j<D;j++){
			if(M[i][j]!=-1)//No hay bomba en esa posición
				M[i][j]=bombas_alrededor(M,i,j);
		}
	}
}
bombas_alrededor(int M[D][D],int i,int j){//suma 1 a la variable bombas si hay una bomba tocando(aunque se por las esquinas) a la posición inicial
	int bombas=0;
	if(M[i][j+1]==-1)
		bombas++;
	if(M[i][j-1]==-1)
		bombas++;
	if(M[i-1][j]==-1)
		bombas++;
	if(M[i+1][j]==-1)
		bombas++;
	if(M[i+1][j+1]==-1)
		bombas++;
	if(M[i-1][j+1]==-1)
		bombas++;
	if(M[i+1][j-1]==-1)
		bombas++;
	if(M[i-1][j-1]==-1)
		bombas++;
	return bombas;
}
