#include<stdio.h>
#define N 10
void avanzar_4_sentidos(int M[N][N],int coord_x,int coord_y,int,int);
void imprime_matriz(int M[N][N], int f, int c);
int main (){
	int mapa[N][N]={
	{ 0, 0, 0,-1, 0, 0,-1, 0, 0, 0},
	{ 0, 0, 0,-1, 0, 0,-1, 0,-1, 0},
	{-1,-1, 0,-1,-1,-1,-1, 0,-1, 0},
	{ 0, 0, 0, 0, 0, 0,-1, 0,-1, 0},
	{ 0, 0,-1,-1, 0,-1,-1, 0,-1, 0},
	{ 0, 0, 0,-1, 0, 0, 0, 0,-1, 0},
	{ 0,-1, 0, 0, 0, 0,-1, 0,-1, 0},
	{ 0, 0, 0,-1, 0, 0,-1, 0,-1, 0},
	{-1,-1,-1,-1,-1, 0,-1,-1,-1, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	};
	int coord_x,coord_y,x_ini=0,y_ini=9;
	mapa[x_ini][y_ini]=1;
	scanf("%i %i",&coord_x,&coord_y);
	avanzar_4_sentidos(mapa,coord_x,coord_y,x_ini,y_ini);
	printf("\n\n");
	imprime_matriz(mapa,N,N);

	return 0;
}
	

void avanzar_4_sentidos(int M[N][N],int x,int y,int x_inicial,int y_inicial){// Función recursiva que repite una rama hasta que choque con una pared(-1), se salga de la matriz, haya una rama más corta que llega a la meta o se corte con una rama más corta para llegar a la meta
	if(M[x][y]==0||M[x_inicial][y_inicial]<M[x][y]-1){ //para que siga por esa rama, se tiene que no haber llegado a la meta o que vaya por un numero inferior al que hay en la meta
	
		if(x_inicial-1>=0&&x_inicial-1<N&&y_inicial<N&&y_inicial>=0&&M[x_inicial-1][y_inicial]>=0&&(M[x_inicial-1][y_inicial]==0||M[x_inicial][y_inicial]+1<M[x_inicial-1][y_inicial])){ // no avanzar si hay un menos 1(pared) o si se va a salir de la matriz o si hay un numero inferior en la casilla que va a ocupar
			M[x_inicial-1][y_inicial]=M[x_inicial][y_inicial]+1;//avanza una casi hacía abajo y suma uno al numero de pasos que se uso para llegar a la anterior
			avanzar_4_sentidos(M,x,y,x_inicial-1,y_inicial);
		}
		if(x_inicial+1>=0&&x_inicial+1<N&&y_inicial<N&&y_inicial>=0&&M[x_inicial+1][y_inicial]>=0&&(M[x_inicial+1][y_inicial]==0||M[x_inicial][y_inicial]+1<M[x_inicial+1][y_inicial])){
			M[x_inicial+1][y_inicial]=M[x_inicial][y_inicial]+1;
			avanzar_4_sentidos(M,x,y,x_inicial+1,y_inicial);
		}
		if(x_inicial>=0&&x_inicial<N&&y_inicial-1<N&&y_inicial-1>=0&&M[x_inicial][y_inicial-1]>=0&&(M[x_inicial][y_inicial-1]==0||M[x_inicial][y_inicial]+1<M[x_inicial][y_inicial-1])){
			M[x_inicial][y_inicial-1]=M[x_inicial][y_inicial]+1;		
			avanzar_4_sentidos(M,x,y,x_inicial,y_inicial-1);
		}
		if(x_inicial>=0&&x_inicial<N&&y_inicial+1<N&&y_inicial+1>=0&&M[x_inicial][y_inicial+1]>=0&&(M[x_inicial][y_inicial+1]==0||M[x_inicial][y_inicial]+1<M[x_inicial][y_inicial+1])){
			M[x_inicial][y_inicial+1]=M[x_inicial][y_inicial]+1;		
			avanzar_4_sentidos(M,x,y,x_inicial,y_inicial+1);
		}		
	}

	system("cls");
	imprime_matriz(M,N,N);
	if(M[x][y]<=0)// si la posición (x,y) vale 0 significa que aun no se llegó a dicho punto
		printf("\nNo se llego a la meta");
	else
		printf("\nEl camino mas corto es de %i pasos",M[x][y]-1);
}



void imprime_matriz(int M[N][N], int f, int c)
{
int i, j;
for(i = 0; i < f; i++) {
for(j = 0; j < c; j++){
if(M[i][j]>=0&&M[i][j]<10)
printf(" ");//para que los numeros de un digito ocupen lo mismo que los de 2 o los negativos mayores que -10
printf(" %d ", M[i][j]);
}
printf("\n");
}
}

