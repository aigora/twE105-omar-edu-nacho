#include<stdio.h>
#include <time.h>
#define N 20 //dimension matriz cuadrada
#define L N*N //dimension vectores
typedef struct{
	int x,y;
}punto;
void avanzar_4_sentidos(int M[N][N],int coord_x,int coord_y,int,int,punto punto_camino[L],int v_x[L],int v_y[L],int contador);
void imprime_matriz(int M[N][N]);
int Pregunta(int v_x[L],int v_y[L],int x,int y,int *resta);//Comprueba si una posición está en los vectores (v_x,v_y)
void imprime_matriz_con_flechas(int M[N][N],int v_x[L],int v_y[L]);
void imprime_matriz_jugar(int M[N][N],int,int,int,int);//imprime matriz con O en la posicion x,y
int jugar(int M[N][N],int,int,int,int);//controla como va a jugar el usuario
int condiciones(int M[N][N],int,int,int,int);
void Copiar_vector(int v1[L],int v2[L]);

int main (){
	empezar_de_nuevo:
	system("color f0");
	punto puntos_camino[L];
	int coord_x,coord_y,x_ini,y_ini,i,pasos,mapa[N][N]={
	{ 0, 0, 0,-1,-1,-1,-1, 0, 0, 0,-1,-1,-1,-1,-1,-1,-1, 0, 0, 0},
	{-1,-1, 0, 0, 0, 0,-1, 0,-1, 0, 0, 0, 0, 0, 0,-1, 0,-1,-1, 0},
	{-1,-1,-1,-1,-1, 0,-1, 0,-1,-1,-1,-1,-1,-1,-1, 0,-1, 0,-1, 0},
	{ 0, 0, 0, 0, 0, 0,-1, 0, 0, 0,-1,-1,-1,-1,-1, 0,-1, 0,-1, 0},
	{ 0,-1,-1, 0,-1,-1,-1, 0,-1, 0, 0, 0, 0, 0, 0, 0,-1, 0,-1, 0},
	{ 0, 0, 0, 0, 0, 0,-1, 0, 0, 0,-1,-1,-1,-1,-1, 0,-1, 0,-1, 0},
	{-1,-1,-1,-1, 0,-1,-1, 0,-1, 0, 0,-1,-1,-1,-1, 0,-1, 0,-1, 0},
	{ 0, 0, 0,-1, 0, 0, 0, 0,-1,-1, 0, 0, 0, 0,-1, 0,-1, 0,-1, 0},
	{-1,-1,-1,-1,-1,-1,-1, 0,-1,-1,-1,-1,-1, 0,-1,-1,-1, 0,-1, 0},
	{ 0, 0, 0, 0, 0, 0,-1, 0, 0, 0,-1,-1,-1, 0, 0, 0,-1, 0,-1, 0},
	{ 0, 0, 0,-1,-1,-1,-1, 0,-1, 0, 0, 0,-1,-1,-1, 0,-1, 0,-1, 0},
	{-1,-1, 0, 0, 0, 0, 0, 0,-1, 0, 0,-1, 0, 0,-1, 0,-1, 0,-1, 0},
	{-1,-1,-1,-1,-1, 0,-1,-1,-1, 0,-1,-1, 0,-1,-1, 0,-1, 0,-1, 0},
	{ 0, 0, 0, 0, 0, 0,-1, 0, 0,-1,-1,-1, 0,-1,-1, 0,-1, 0,-1, 0},
	{ 0,-1,-1, 0,-1,-1,-1, 0,-1, 0, 0, 0, 0,-1,-1, 0,-1, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0,-1, 0, 0, 0,-1,-1, 0,-1,-1, 0,-1, 0,-1, 0},
	{-1,-1,-1,-1, 0,-1, 0, 0,-1, 0,-1,-1, 0, 0,-1, 0,-1, 0,-1, 0},
	{ 0, 0, 0,-1, 0, 0, 0, 0,-1, 0,-1,-1,-1, 0,-1, 0, 0, 0,-1, 0},
	{-1,-1,-1,-1,-1, 0,-1,-1,-1, 0,-1,-1,-1, 0,-1, 0,-1, 0,-1, 0},
	{ 0, 0, 0, 0, 0, 0,-1, 0, 0, 0,-1,-1,-1, 0,-1, 0,-1, 0,-1, 0},
	};
	int v_x[L]={0},v_y[L]={0},j,Pregunta_jugar;//matriz para guardar listas para seguir el camino recorrdido(3=derecha,4=izq,1=arriba,2=abajo)
	double t0,t1,t2,t3,time_usuario,time_maquina,t4,t5,tiempo;
	imprime_matriz(mapa);
	printf("\n\tcoordenadas de la posicion inicial x0 y0: ");
	scanf("%i %i",&x_ini,&y_ini);
	printf("\n\tcoordenadas de la posicion final x y: ");
	scanf(" %i %i",&coord_x,&coord_y);
	printf("\n\tTe atreves con el laberinto? \n\n\tSi quieres jugar pulsa 1 y si tienes miedo pulsa cualquier otro caracter: ");
	scanf(" %i",&Pregunta_jugar);
	x_ini--;y_ini--;coord_x--;coord_y--;
	mapa[x_ini][y_ini]=1;//Si hay pared(-1) en la posicion inicial o final, la quito 
	mapa[coord_x][coord_y]=0;
	if(Pregunta_jugar==1){
		t0=clock();
		pasos=jugar(mapa,x_ini,y_ini,coord_x,coord_y);
		t1=clock();
		time_usuario=(t1-t0)/(double)CLOCKS_PER_SEC;
		system("cls");
		printf("\n\tHas tardado %lf segundos y lo has hecho en %i pasos",time_usuario,pasos);
		printf("\n\n\tLa verdad pensaba que no lo ibas a lograr\n\n");
		getch();	
		printf("\tBueno, Ahora me toca a mi, que los humanos sois muy lentos para estas cosas");
		getch();
	}
	else{
	printf("\n\tVeo que no te atraves\n\n\tBueno ya lo resuelvo yo por ti");
	getch();
	}
	puntos_camino[0].x=x_ini;
	puntos_camino[0].y=y_ini;
	t2=clock();
	avanzar_4_sentidos(mapa,coord_x,coord_y,x_ini,y_ini,puntos_camino,v_x,v_y,1);
	t3=t4=clock();
	time_maquina=(t3-t2)/(double)CLOCKS_PER_SEC;
	printf("\n\n");
	if(mapa[coord_x][coord_y]!=0){
	printf("\tEl camino mas corto es de %i pasos\n",mapa[coord_x][coord_y]-1);	
	printf("\n\tNo es por nada, pero solo he tardado %0.15lf segundos \n\n\tEste es el camino seguido\n\n",time_maquina);
	imprime_matriz_con_flechas(mapa,v_x,v_y);
	t5=clock();
	tiempo=(t5-t4)/(float)CLOCKS_PER_SEC;
	printf("\n%f segundos",tiempo);
	}
	else // si la posición (coord_x,coord_y) vale 0 significa que no se puede llegar a la meta
		printf("\tNo se llego a la meta\n");
	
	printf("\n\n\tQuieres seguir jugado? Pulsa 1:");
	scanf("%i",&Pregunta_jugar);
	if(Pregunta_jugar==1){
		system("cls");
		goto empezar_de_nuevo;
	}
	else
		printf("Hasta la proxima");
	return 0;
}
	
int condiciones(int M[N][N],int xi,int yi,int xf,int yf){//Para que devuelva 1 no tiene que haber pared(-1) en la posición a la que se mueve y no se sale de las dimensiones de la matriz
	if(xf>=0&&xf<N&&yf<N&&yf>=0&&M[xf][yf]!=-1 && (M[xf][yf]==0 || M[xi][yi]+1<M[xf][yf]))//Y también en la posición en la que se va a avanzar tiene que haber un cero o que se va a mejorar al menos por uno al número que ya hay allí
		return 1;
	else 
		return 0;
}

void avanzar_4_sentidos(int M[N][N],int x,int y,int x_inicial,int y_inicial,punto puntos_camino[L],int v_x[L],int v_y[L],int contador){// Función recursiva que repite una rama hasta que choque con una pared(-1), se salga de la matriz, haya una rama más corta que llega a la meta o se corte con una rama más corta para llegar a la meta

	if(M[x][y]==0||M[x_inicial][y_inicial]+1<M[x][y]){ //para que siga por esa rama, no se tiene que haber llegado a la meta o que vaya por un numero inferior al que hay en la meta
	
		if(condiciones(M,x_inicial,y_inicial,x_inicial-1,y_inicial)){
			M[x_inicial-1][y_inicial]=M[x_inicial][y_inicial]+1;//avanza una hacía abajo y suma uno al numero de pasos que se uso para llegar a la anterior
			puntos_camino[contador].x=x_inicial-1;
			puntos_camino[contador].y=y_inicial;//Las posiciones por las que se expande se guardan en vector_x y vector_y, en la posición contador
			avanzar_4_sentidos(M,x,y,x_inicial-1,y_inicial, puntos_camino, v_x, v_y,contador+1);
		}
		if(condiciones(M,x_inicial,y_inicial,x_inicial+1,y_inicial)){
			M[x_inicial+1][y_inicial]=M[x_inicial][y_inicial]+1;
			puntos_camino[contador].x=x_inicial+1;
			puntos_camino[contador].y=y_inicial;
			avanzar_4_sentidos(M,x,y,x_inicial+1,y_inicial,puntos_camino, v_x, v_y,contador+1);
		}
		if(condiciones(M,x_inicial,y_inicial,x_inicial,y_inicial-1)){
			M[x_inicial][y_inicial-1]=M[x_inicial][y_inicial]+1;
			puntos_camino[contador].x=x_inicial;
			puntos_camino[contador].y=y_inicial-1;		
			avanzar_4_sentidos(M,x,y,x_inicial,y_inicial-1,puntos_camino, v_x, v_y,contador+1);
		}
		if(condiciones(M,x_inicial,y_inicial,x_inicial,y_inicial+1)){
			M[x_inicial][y_inicial+1]=M[x_inicial][y_inicial]+1;
			puntos_camino[contador].x=x_inicial;
			puntos_camino[contador].y=y_inicial+1;		
			avanzar_4_sentidos(M,x,y,x_inicial,y_inicial+1, puntos_camino, v_x, v_y,contador+1);
		}		
	}	
	if(x_inicial==x&&y_inicial==y){//cuando está en la meta, guarda el camino recorrido en v_x y v_y, el programa está hecho de forma que solo puede llegar a la meta, mejorando el camino anterior
		int i;//Por lo que se acabará guardando el camino más corto
		for(i=contador;i<L;i++)//Antes de pasar el camino a v_x y v_y, se limpia lo que se guardó en las siguientes posiciones a la que se llego a la meta 
			puntos_camino[i].x=puntos_camino[i].y=0;
		for(i=0;i<L;i++){//Copiando el camio en los vectores v_x y v_y
			v_x[i]=puntos_camino[i].x;
			v_y[i]=puntos_camino[i].y;
		}
	}
}

void imprime_matriz(int M[N][N]){
	int i, j;
	printf("\t");
	for(i=1;i<=N;i++){
		if(i<10)
			printf(" ");//Se desalineban los números de las columnas al ser de 2 digitos, así se arregla
		printf(" %i ",i);
	}
	printf("\n\n\n");
	for(i = 0; i < N; i++) {
		printf("%i\t",i+1);
		for(j = 0; j < N; j++){
			if(M[i][j]==-1)
				printf("  X ");
			else{
				 if(M[i][j]>=0&&M[i][j]<10)
					printf(" ");//para que los numeros de un digito ocupen lo mismo que los de 2
					if(M[i][j]==0)
						printf(" . ");
					else
						printf(" %d ", M[i][j]);
				}
		}
		printf("\n");
	}
}

int Pregunta(int v_x[L],int v_y[L],int x,int y,int *resta){
	int i,j=2;
	*resta=0;
	for(i=0;i<L;i++){
		if(v_x[i]==x&&v_y[i]==y){// devuelve 2 si no está esa posición en los vectores y 1,-1 o 0 dependiendo de si se desplaza a la derecha, izquierda o (abajo o arriba) respectivamente
			j=v_y[i]-v_y[i-1];
			*resta=v_x[i]-v_x[i-1];
			break;
		}
	}
	return j;
}
void imprime_matriz_con_flechas(int M[N][N],int v_x[L],int v_y[L]){
	int i,j,pregunta,resta_arriba=0;
	for(i=0;i<N;i++){
		printf("\t");
		for(j=0;j<N;j++){
			if(i!=0||j!=0)
				pregunta=Pregunta(v_x,v_y,i,j,&resta_arriba);
			if(M[i][j]==-1)//Si hay -1 en esta posicion que dibuje una X
				printf("  . ");
			else if(i==v_x[0]&&j==v_y[0])
				printf("  O ");
			else if(resta_arriba==1)
					printf("  v ");// simbolo flecha hacia arriba
			else if(resta_arriba==-1)
				printf("  ^ ");
			else if(pregunta==1)
				printf("  > ");
			else if(pregunta==-1)
				printf("  < ");
			else
				printf("  . ");
		}
		printf("\n");		
	}	
}

int jugar(int mapa[N][N],int xi,int yi,int xf,int yf){
	system("cls");
	printf("\n\tIntenta llegar por el camino mas corto:\n\n");
	printf("\tw=arriba\n\td=derecha\n\ts=abajo\n\ta=izquierda\n");
	imprime_matriz_jugar(mapa,xi,yi,xf,yf);
	int pasos=0;
	char avanzar;
	while(xi!=xf||yi!=yf){//Mientras no se alcanzo la meta
		avanzar=getch();
		switch(avanzar){
			case 'w'://arriba
				if(mapa[xi-1][yi]!=-1&&xi-1>=0){//Si no hay menos uno en esa posición (pared) y que no se salga de la matriz
					xi--;
					system("cls");
					imprime_matriz_jugar(mapa,xi,yi,xf,yf);
					pasos++;
				}
			break;
			case 's'://abajo
				if(mapa[xi+1][yi]!=-1&&xi+1<=N-1){
					xi++;
					system("cls");
					imprime_matriz_jugar(mapa,xi,yi,xf,yf);
					pasos++;
				}
			break;
			case 'd'://derecha
				if(mapa[xi][yi+1]!=-1&&yi+1<=N-1){
					yi++;
					system("cls");
					imprime_matriz_jugar(mapa,xi,yi,xf,yf);
					pasos++;
				}
			break;
			case 'a'://izquierda
				if(mapa[xi][yi-1]!=-1&&yi-1>=0){
					yi--;
					system("cls");
					imprime_matriz_jugar(mapa,xi,yi,xf,yf);
					pasos++;
				}
			break;
			default:
				printf("No valido");
		}	
	}
	return pasos;
}

void imprime_matriz_jugar(int M[N][N],int xi,int yi,int xf,int yf){
	int i, j;
	printf("\n");
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++){
			if(i==xi&&j==yi)// dibuja O en la posicion actual
				printf("  O ");
			else if(M[i][j]==-1)
				printf("  X ");
			else if(i==xf&&j==yf)// dibuja M en la meta
				printf("  M ");
			else
				printf("  . ");	
			}
		printf("\n");
	}
}
