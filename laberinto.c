#include<stdio.h>
void avanzar_4_sentidos(int M[10][10],int coord_x,int coord_y,int,int);
void imprime_matriz(int M[10][10], int f, int c);
int main (){
	int mapa[10][10]={
	{ 0, 0, 0, 0, 0, 0,-1, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0,-1, 0,-1, 0},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1, 0},
	{ 0, 0, 0, 0, 0, 0,-1, 0,-1, 0},
	{ 0, 0,-1,-1,-1,-1,-1, 0,-1, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0,-1, 0},
	{ 0, 0, 0, 0, 0, 0,-1, 0,-1, 0},
	{ 0, 0, 0,-1, 0, 0,-1, 0,-1, 0},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	};
	int coord_x,coord_y,x_ini=0,y_ini=9;
	mapa[x_ini][y_ini]=1;
	scanf("%i %i",&coord_x,&coord_y);
	imprime_matriz(mapa,10,10);

	avanzar_4_sentidos(mapa,coord_x,coord_y,x_ini,y_ini);

	return 0;
}

void avanzar_4_sentidos(int M[10][10],int x,int y,int x_inicial,int y_inicial){
	if(M[x][y]==0||M[x_inicial][y_inicial]<M[x][y]-1){ //para que siga por esa rama, se tiene que no haber llegado a la meta o que vaya por un numero inferior al que hay en la meta
	
		if(x_inicial-1>=0&&x_inicial-1<10&&y_inicial<10&&y_inicial>=0&&M[x_inicial-1][y_inicial]>=0&&(M[x_inicial-1][y_inicial]==0||M[x_inicial][y_inicial]+1<M[x_inicial-1][y_inicial])){ // no avanzar si hay un menos 1(pared) o si se va a salir de la matriz o si hay un numero inferior en la casilla que va a ocupar
			M[x_inicial-1][y_inicial]=M[x_inicial][y_inicial]+1;
			avanzar_4_sentidos(M,x,y,x_inicial-1,y_inicial);
		}
		if(x_inicial+1>=0&&x_inicial+1<10&&y_inicial<10&&y_inicial>=0&&M[x_inicial+1][y_inicial]>=0&&(M[x_inicial+1][y_inicial]==0||M[x_inicial][y_inicial]+1<M[x_inicial+1][y_inicial])){
			M[x_inicial+1][y_inicial]=M[x_inicial][y_inicial]+1;
			avanzar_4_sentidos(M,x,y,x_inicial+1,y_inicial);
		}
		if(x_inicial>=0&&x_inicial<10&&y_inicial-1<10&&y_inicial-1>=0&&M[x_inicial][y_inicial-1]>=0&&(M[x_inicial][y_inicial-1]==0||M[x_inicial][y_inicial]+1<M[x_inicial][y_inicial-1])){
			M[x_inicial][y_inicial-1]=M[x_inicial][y_inicial]+1;		
			avanzar_4_sentidos(M,x,y,x_inicial,y_inicial-1);
		}
		if(x_inicial>=0&&x_inicial<10&&y_inicial+1<10&&y_inicial+1>=0&&M[x_inicial][y_inicial+1]>=0&&(M[x_inicial][y_inicial+1]==0||M[x_inicial][y_inicial]+1<M[x_inicial][y_inicial+1])){
			M[x_inicial][y_inicial+1]=M[x_inicial][y_inicial]+1;		
			avanzar_4_sentidos(M,x,y,x_inicial,y_inicial+1);
		}		
	}
	system("cls");
	imprime_matriz(M,10,10);
	if(M[x][y]==0)
	printf("\nNo se llegamos a la meta");
	else
	printf("\nBuscando camino mas corto");
}



void imprime_matriz(int M[10][10], int f, int c)
{
int i, j;
for(i = 0; i < f; i++) {
for(j = 0; j < c; j++)
printf(" %d ", M[i][j]);
printf("\n");
}
}

