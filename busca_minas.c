#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define D 10//dimensión de la matriz

typedef struct{
	int x,y;
	char letra;
}punto;

void imprime_matriz(int M[D][D]);// imprime la matriz poniendo X en lugar de los -1 (bombas)
void crear_buscaminas(int M[D][D]);//pone en cada casilla el número de bombas que tiene alrededor
int bombas_alrededor(int M[D][D],int i,int j);//cuenta el numero de bombas alrededor de una posición (i,j)
int jugar(int M[D][D],punto puntos[D*D],int num_puntos);//imprime los elementos de la matriz como ".", menos los que están en la varaible puntos (que son los puntos que elige el usuario)
int dentro_matriz(int M[D][D],int x,int y);//compueba si una posición está dentro de una matriz
void Expandir(int M[D][D],punto pts[D*D],int *num_pts,int x,int y);//muestra todos los valores cerca del 0 y vuelve a expandirse por cada uno de estos valor(es una función recursiva)
void agregar(punto pts[D*D],int num_pts,int ,int y);//Le añade al vector puntos un punto en la posición num_pts
int esta_en_vector(punto puntos[D*D],int,int,int);//pregunta

int main(){
	empezar:
	system("color f9");
	char letra,letras[D*D];
	int random,bombas=0,Mapa[D][D]={0,0,0},fila,columna,num_puntos=0,x,y,i,banderas_usadas,Pregunta_esta,nivel;
	float t1,t2,tiempo;
	punto puntos[D*D]={0,0,0};//vector de la estructura punto
	srand(time(NULL));
	printf("Pon 1, 2 o 3 para eligir el nivel ");
	scanf("%i",&nivel);
	if(nivel==1)nivel=2;
	else if(nivel==2)nivel=4;
	else if(nivel==3)nivel=5;
	else goto empezar;
	for(fila=0;fila<D;fila++){//Pone bombas de forma aleatoria
		for(columna=0;columna<D;columna++){
			random = rand() % 10 + 1;
			if(random<nivel){//Va recorriendo la matriz y generando números random, si son menores que 5 pone una bomba(-1) en esa posición
				Mapa[fila][columna]=-1;
				bombas++;
			}
		}
	}
	system("cls");
	crear_buscaminas(Mapa);
	jugar(Mapa,puntos,0);
	printf("\nHay %i bombas\n\nHay que poner las coordenadas y despues A o O\n\n-A es para ver lo que hay en esa casilla \n\n-O para poner bandera\n\nEjem: 1 1 A\n\n",bombas);
	t1=clock();
	do{
		scanf("%i %i %c",&x,&y,&letra);//O poner bandera y A ver que hay en la casilla (abrir casilla)
		if(banderas_usadas>=bombas&&letra=='O'){
			printf("Si quieres usar mas banderas, quita alguna usada\nVuelve a introducir las coordenadas y la letra\n");
			do{
				scanf("%i %i %c",&x,&y,&letra);
			}while(letra=='O');
		}
		x--;y--;// se resta uno porque el mapa va de 1 a D, y la matriz va de 0 a D-1
		if(dentro_matriz(Mapa,x,y)==0||(letra!='A'&&letra!='O')){
			printf("\nError\nEscribe las coordenadas de nuevo\n");
			do{
				scanf("%i %i %c",&x,&y,&letra);
				x--;y--;
			}while(dentro_matriz(Mapa,x,y)==0||(letra!='A'&&letra!='O'));
		}
		if(Mapa[x][y]==-1&&letra=='A'){
			system("cls");
			imprime_matriz(Mapa);
			printf("\nHas perdido");
			break;
		}
		else{
			Pregunta_esta=esta_en_vector(puntos,num_puntos,x,y);
			if(Pregunta_esta!=-1)
				puntos[Pregunta_esta].letra=letra;
			
			else{//si no está que lo añada a la estructura puntos
				puntos[num_puntos].x=x;
				puntos[num_puntos].y=y;
				puntos[num_puntos].letra=letra;
				num_puntos++;
				if(Mapa[x][y]==0&&letra=='A')
					Expandir(Mapa,puntos,&num_puntos,x,y);
			}
			system("cls");
			banderas_usadas=jugar(Mapa,puntos,num_puntos);
			if(banderas_usadas==-1){
				t2=clock();
				tiempo=(t2-t1)/(float)CLOCKS_PER_SEC;
				printf("\nHAS GANADO y has tardado %i minutos y %i segundos",(int)tiempo/60,(int)tiempo%60);//pone el tiempo en minutos y segundos
				break;	
			}
			printf("\nTe quedan %i banderas por usar\n",bombas-banderas_usadas);
		}
	}while(1);
	printf("\nQuieres jugar de nuevo? Pulsa 1: ");
	if(getch()=='1'){
		system("cls");
		goto empezar;
	}
	return 0;
}

void imprime_matriz(int M[D][D]){
	int i,j;
	printf(" \t");
	for(i=1;i<=D;i++){
		if(i<10)
			printf(" ");
		printf(" %i ",i);
	}
	printf("\n\n");
	for(i=0;i<D;i++){
		printf("%i\t",i+1);
		for(j=0;j<D;j++){
			if(M[i][j]==-1)
				printf("  X ");
			else
				printf("  %i ",M[i][j]);
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

bombas_alrededor(int M[D][D],int x,int y){//suma 1 a la variable bombas si hay una bomba tocando(aunque se por las esquinas) a la posición inicial
	int bombas=0,i,j;
	for(i=-1;i<=1;i++)
		for(j=-1;j<=1;j++)
			if(M[x+i][y+j]==-1&&dentro_matriz(M,x+i,y+j))
				bombas++;
	return bombas;
}

int dentro_matriz(int M[D][D],int x,int y){
	if(x>=0&&x<D&&y>=0&&y<D)// si está dentro de la matriz que devuelva 1, sino que devuelva 0
		return 1;
	else 
		return 0;
}
	
int jugar(int M[D][D],punto puntos[D*D],int num_puntos){
	int i,j,n,pintado=0,banderas=0,Pregunta_ganar=1;
	printf(" \t");
	for(i=1;i<=D;i++){// pintar números del 1 al D arriba
		if(i<10)
			printf(" ");
		printf(" %i ",i);
	}
	printf("\n\n");
	for(i=0;i<D;i++){
		printf("%i\t",i+1);// pintar los números del 1 al D en el lateral izquierdo
		for(j=0;j<D;j++){
			for(n=0,pintado=0;n<num_puntos;n++){
				if(i==puntos[n].x&&j==puntos[n].y){//Si este punto fue eligido por el usuario
					if(puntos[n].letra=='A')//Si ha eligido A (abrir), muestra el numero
						printf("  %i ",M[i][j]);//va a ser un número del 0 al 8
					else if(puntos[n].letra=='O'){//Si ha eligido O (bandera) dibuja O
						printf("  O ");
						banderas++;
					}
					pintado=1;
					break;
				}
			}
			if(pintado==0){
				printf("  . ");
				Pregunta_ganar=0;//Si se dibuja un punto, significa que no está toda resuelta
			}//pero si no se dibuja ningun punto, significa que ya estña resuelta y devolverá -1
		}
		printf("\n");	
	}
	if(Pregunta_ganar==1)
		return -1;//-1 es ganar la partida
	return banderas;
}

void Expandir(int M[D][D],punto pts[D*D],int *num_pts,int x,int y){
	int i,j;
	for(i=-1;i<=1;i++)
		for(j=-1;j<=1;j++)
			if(dentro_matriz(M,x+i,y+j)&&esta_en_vector(pts,*num_pts,x+i,y+j)==-1){//&&(i!=0||j!=0)La última condición es para que no vuelva a agregar un el punto inicial
				agregar(pts,*num_pts,x+i,y+j);
				*num_pts+=1;
				if(M[x+i][y+j]==0)
					Expandir(M,pts,num_pts,x+i,y+j);
			}
}

void agregar(punto pts[D*D],int num_pts,int x,int y){
	pts[num_pts].x=x;
	pts[num_pts].y=y;
	pts[num_pts].letra='A';
}

int esta_en_vector(punto puntos[D*D],int num_ptos,int x,int y){//devuelve -1, si no está en el vector y si esta devuelve el número de la posición
	int i;
	for(i=0;i<num_ptos;i++)//para comprobar que el punto ya está y solo se le cambia la letra (de A a O, o de O a A)
		if(puntos[i].x==x&&puntos[i].y==y)
			return i;
	return -1;
}

