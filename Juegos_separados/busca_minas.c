#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define d 10//dimensi�n de la matriz
#define D 20
typedef struct{//Estructura con coordenadas del punto y a cada punto va asociada una letra
	int x,y;
	char letra;
}punto_letra;
typedef struct{
	char nombre[30];
	int punt;
}usuario;
void imprime_matriz_busca(int M[d][d]);// imprime la matriz poniendo X en lugar de los -1 (bombas)
int crear_buscaminas(int M[d][d],int nivel);//pone en cada casilla el n�mero de bombas que tiene alrededor
int bombas_alrededor(int M[d][d],int i,int j);//cuenta el numero de bombas alrededor de una posici�n (i,j)
int jugar(int M[d][d],punto_letra puntos[d*d],int num_puntos);//imprime los elementos de la matriz como ".", menos los que est�n en la varaible puntos (que son los puntos que ha eligido el usuario)
int dentro_matriz(int M[d][d],int x,int y);//compueba si una posici�n est� dentro de una matriz
void Expandir(int M[d][d],punto_letra pts[d*d],int *num_pts,int x,int y);//Es invocada cuando se elige una posici�n donde hay un cero ,muestra todos los valores cerca del 0 y si repite la funci�n en esos n�meros si hay un cero (funci�n recursiva)
void agregar(punto_letra pts[d*d],int num_pts,int x,int y);//Le a�ade al vector puntos un punto en la posici�n num_pts
int esta_en_vector(punto_letra puntos[d*d],int num_ptos,int x,int y);//Comprueba si el punto (x,y) est� en el vector puntos, num_ptos es el n�mero de elementos del vector
void Puntuaciones(usuario lista_punt[D],FILE *leer);

int main(){
	empezar_bus:
	system("color f9");
	FILE *agregar_archivo=fopen("puntuacion_buscaminas.txt","a");
	if(agregar_archivo==NULL){
		printf("error");
		return 1;
	}
	char letra,letras[d*d],Nickname[20];
	usuario lista_punt[D]={{"iniciamos",0}};
	int random,bombas=0,Mapa[d][d]={0,0,0},fila,columna,num_puntos=0,x,y,i,banderas_usadas,Pregunta_esta,nivel,dif='A'-'a',Puntuacion;
	float t1,t2,tiempo;
	punto_letra puntos[d*d]={0,0,0};//vector de la estructura punto
	printf("\n\tPon 1, 2 o 3 para eligir el nivel ");
	scanf("%i",&nivel);//Elige el nivel 1,2 o 3
	if(nivel==1)nivel=2;
	else if(nivel==2)nivel=3;
	else if(nivel==3)nivel=5;
	else goto empezar_bus;
	system("cls");
	bombas=crear_buscaminas(Mapa,nivel);//Devuelve el n�mero de bombas del mapa
	jugar(Mapa,puntos,0);//Imprime mapa
	printf("\nHay %i bombas\n\nHay que poner las coordenadas y despues A o B\n\n-A es para abrir casilla \n\n-B para poner bandera\n\nEjem: 1 1 A\n\n",bombas);
	t1=clock();//empieza a contar el tiempo
	do{
		scanf("%i %i %c",&x,&y,&letra);//EScanea posici�n (x,y) y letra si es B=poner bandera y A=abrir casilla
		x--;y--;// se resta uno porque el mapa va de 1 a d, y la matriz va de 0 a d-1
		if(banderas_usadas>=bombas&&letra=='B'){//Si usa m�s banderas que el n�mero de bombas que hay
			printf("Si quieres usar mas banderas, quita alguna usada\nVuelve a introducir las coordenadas y la letra\n");
			do{
				scanf("%i %i %c",&x,&y,&letra);
				x--;y--;
			}while(letra=='B'&&dentro_matriz(Mapa,x,y));
		}
		if(letra>='a'&&letra<='z')	letra+=dif;//Si la pone minuscula la pasa a mayuscula
		if(dentro_matriz(Mapa,x,y)==0||(letra!='A'&&letra!='B')){//Si las coordenadas no est�n en la matriz o puso una letra distinta de A y B
			printf("\nError\nEscribe las coordenadas de nuevo\n");
			do{
				scanf("%i %i %c",&x,&y,&letra);
				x--;y--;
				if(letra>='a'&&letra<='z')	letra+=dif;//Si la pone minuscula la pasa a mayuscula
			}while(dentro_matriz(Mapa,x,y)==0||(letra!='A'&&letra!='B'));
		}
		if(Mapa[x][y]==-1&&letra=='A'){
			system("cls");
			imprime_matriz_busca(Mapa);
			printf("\n\tHas perdido");
			break;//Sale del Do-While
		}
		else{
			Pregunta_esta=esta_en_vector(puntos,num_puntos,x,y);//Ver si la coordenadas introducida en est� en el vector puntos
			if(Pregunta_esta!=-1)
				puntos[Pregunta_esta].letra=letra;
			
			else{//si no est� que lo a�ada a la estructura puntos
				puntos[num_puntos].x=x;
				puntos[num_puntos].y=y;
				puntos[num_puntos].letra=letra;
				num_puntos++;//contador de puntos en la estructura puntos
				if(Mapa[x][y]==0&&letra=='A')	Expandir(Mapa,puntos,&num_puntos,x,y);//Si hay un cero que se expanda
			}
			system("cls");
			banderas_usadas=jugar(Mapa,puntos,num_puntos);//jugar devuelve las banderas usadas y -1 si ha ganado
			///////Ha ganado///////
			if(banderas_usadas==-1){
				t2=clock();
				tiempo=(t2-t1)/(float)CLOCKS_PER_SEC;//Calcula tiempo que se ha tardado en resolverlo
				printf("\n\n\tHAS GANADO y has tardado %i minutos y %i segundos",(int)tiempo/60,(int)tiempo%60);//pone el tiempo en formato minutos y segundos (No se puede hacer en menos de un minuto)
				Puntuacion=nivel*1000000/(int)tiempo;;
				printf("\n\n\tTu puntuacion es %i",Puntuacion);
				printf("\n\tPon Nombre: ");
				scanf(" %[^\n]",Nickname);
				fprintf(agregar_archivo,"%s.%i\n",Nickname,Puntuacion);
				i=0;
				fclose(agregar_archivo);
				FILE *leer_archivo=fopen("puntuacion_buscaminas.txt","r");
				Puntuaciones(lista_punt,leer_archivo);
				system("cls");
				printf("\t   Nombre \t Puntuacion");
				for(i=0;lista_punt[i].punt!=0&&i<10;i++)
					printf("\n\t%i- %s \t %i",i+1,lista_punt[i].nombre,lista_punt[i].punt);
				fclose(leer_archivo);
				break;	
			}
			printf("\n\tTe quedan %i banderas por usar\n",bombas-banderas_usadas);
		}
	}while(1);
	printf("\n\tQuieres jugar de nuevo? Pulsa 1: ");
	if(getch()=='1'){
		system("cls");
		goto empezar_bus;
	}
	return 0;
}

void imprime_matriz_busca(int M[d][d]){
	int i,j;
	printf(" \t");
	for(i=1;i<=d;i++){
		if(i<10)	printf(" ");//Para cuadrar el mapa
		printf(" %i ",i);
	}
	printf("\n\n");
	for(i=0;i<d;i++){
		printf("%i\t",i+1);
		for(j=0;j<d;j++){
			if(M[i][j]==-1)
				printf("  X ");
			else
				printf("  %i ",M[i][j]);
		}
		printf("\n");	
	}
}

int crear_buscaminas(int Mapa[d][d],int nivel){
	int i,j,random,bombas=0;
		srand(time(NULL));
	for(i=0;i<d;i++){//Recorre la matriz y Pone bombas de forma aleatoria en cada casilla,
		for(j=0;j<d;j++){
			random = rand() % 10 + 1;
			if(random<nivel){//Va recorriendo la matriz y generando n�meros random, si son menores que "nivel" pone una bomba(-1) en esa posici�n
				Mapa[i][j]=-1;
				bombas++;
			}
		}
	}
	for(i=0;i<d;++i){
		for(j=0;j<d;j++){
			if(Mapa[i][j]!=-1)//No hay bomba en esa posici�n
				Mapa[i][j]=bombas_alrededor(Mapa,i,j);//Entonces pone en ella el n�mero de bombas que hay alrededor
		}
	}
	return bombas;
}

bombas_alrededor(int M[d][d],int x,int y){//suma 1 a la variable bombas si hay una bomba tocando(aunque se por las esquinas) a la posici�n inicial
	int bombas=0,i,j;
	for(i=-1;i<=1;i++)
		for(j=-1;j<=1;j++)
			if(M[x+i][y+j]==-1&&dentro_matriz(M,x+i,y+j))	bombas++;//Si a su alrededor en esa casilla hay -1 y est� en la matriz, suma uno al n�mero de bombas
	return bombas;
}

int dentro_matriz(int M[d][d],int x,int y){
	if(x>=0&&x<d&&y>=0&&y<d)// si est� dentro de la matriz que devuelva 1, sino que devuelva 0
		return 1;
	else 
		return 0;
}
	
int jugar(int M[d][d],punto_letra puntos[d*d],int num_puntos){
	int i,j,n,pintado=0,banderas=0,Pregunta_ganar=1;
	printf(" \t");
	for(i=1;i<=d;i++){// pintar n�meros del 1 al D arriba
		if(i<10)	printf(" ");//Pone espacio para cuadrar el mapa
		printf(" %i ",i);
	}
	printf("\n\n");
	for(i=0;i<d;i++){
		printf("%i\t",i+1);// pintar los n�meros del 1 al D en el lateral izquierdo
		for(j=0;j<d;j++){
			for(n=0,pintado=0;n<num_puntos;n++){
				if(i==puntos[n].x&&j==puntos[n].y){//Si este punto fue eligido por el usuario
					if(puntos[n].letra=='A')	printf("  %i ",M[i][j]);//Si ha eligido A (abrir), muestra el n�mero
					else if(puntos[n].letra=='B'){//Si ha eligido B (bandera) dibuja B
						printf("  B ");
						banderas++;//Suma el contador de banderas
					}
					pintado=1;//Casilla pintada
					break;
				}
			}
			if(pintado==0){//Si la casilla no fue pintada, pone un punto
				printf("  . ");
				Pregunta_ganar=0;//Si se dibuja un punto, significa que no est� todo el mapa resuelto, por lo tanto, no ha ganado aun
			}//pero si no se dibuja ningun punto, significa que ya est�a resuelta y devolver� -1
		}
		printf("\n");	
	}
	if(Pregunta_ganar==1)
		return -1;//-1 es ganar la partida
	return banderas;
}

void Expandir(int M[d][d],punto_letra pts[d*d],int *num_pts,int x,int y){
	int i,j;
	for(i=-1;i<=1;i++)
		for(j=-1;j<=1;j++)
			if(dentro_matriz(M,x+i,y+j)&&esta_en_vector(pts,*num_pts,x+i,y+j)==-1){//La �ltima condici�n es para que no vuelva a agregar un el punto inicial
				agregar(pts,*num_pts,x+i,y+j);
				*num_pts+=1;//num_ptos es el n�mero de puntso guardados en el vector puntos
				if(M[x+i][y+j]==0)	Expandir(M,pts,num_pts,x+i,y+j);//Se sigue expandiendo si hay un cero en esa posici�n
			}
}

void agregar(punto_letra pts[d*d],int num_pts,int x,int y){
	pts[num_pts].x=x;
	pts[num_pts].y=y;
	pts[num_pts].letra='A';
}

int esta_en_vector(punto_letra puntos[d*d],int num_ptos,int x,int y){//devuelve -1 si no est� en el vector y si est� devuelve el n�mero de la posici�n
	int i;
	for(i=0;i<num_ptos;i++)//para comprobar que el punto ya est� y solo se le cambia la letra (de A a B, o de B a A)
		if(puntos[i].x==x&&puntos[i].y==y)
			return i;
	return -1;
}
void Puntuaciones(usuario lista_punt[D],FILE *leer_archivo){//Ordena el vector de usuarios de mayor (en la posici�n 0) a menor
	usuario aux;
	int i=0,j;
	while(fscanf(leer_archivo,"%[^.].%i\n",lista_punt[i].nombre,&lista_punt[i].punt)!=EOF)
		i++;
	for(i=0;lista_punt[i].punt!=0;i++)
		for(j=i+1;lista_punt[j].punt!=0;j++)
			if(lista_punt[i].punt<lista_punt[j].punt){
				aux=lista_punt[i];
				lista_punt[i]=lista_punt[j];
				lista_punt[j]=aux;
			}
			system("cls");
		printf("\t   Nombre \t Puntuacion");
		for(i=0;lista_punt[i].punt!=0&&i<10;i++)
			printf("\n\t%i- %s \t %i",i+1,lista_punt[i].nombre,lista_punt[i].punt);
}

