#include<stdio.h>
#include <time.h>
#define N 20 //dimension matriz cuadrada
#define L 210 //dimension vectores
void avanzar_4_sentidos(int M[N][N],int coord_x,int coord_y,int,int);
void imprime_matriz(int M[N][N]);
void comprobar(int M[N][N],int xi,int yi,int xf,int yf,int vector_x[],int vector_y[],int contador,int v_x[L],int v_y[L]);
int Pregunta(int v_x[L],int v_y[L],int x,int y,int *resta);//Comprueba si una posición está en los vectores (v_x,v_y)
void imprime_matriz_con_flechas(int M[N][N],int v_x[L],int v_y[L]);
void imprime_matriz_jugar(int M[N][N],int,int,int,int);//imprime matriz con O en la posicion x,y
int jugar(int M[N][N],int,int,int,int);//controla como va a jugar el usuario
int condiciones(int M[N][N],int,int);

int main (){
	empezar_de_nuevo:
	system("color f0");
	int coord_x,coord_y,x_ini,y_ini,vector_x[L]={0},vector_y[L]={0},i,pasos,mapa[N][N]={
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
	t2=clock();
	avanzar_4_sentidos(mapa,coord_x,coord_y,x_ini,y_ini);
	t3=t4=clock();
	time_maquina=(t3-t2)/(double)CLOCKS_PER_SEC;
	
	printf("\n\n");
	if(mapa[coord_x][coord_y]!=0){
	printf("\tEl camino mas corto es de %i pasos\n",mapa[coord_x][coord_y]-1);
	vector_x[0]=x_ini;
	vector_y[0]=y_ini;	
	comprobar(mapa,x_ini,y_ini,coord_x,coord_y,vector_x,vector_y,0,v_x,v_y);
	for(i=mapa[coord_x][coord_y];i<L;i++)//que sea 0 todos lo valores que no nos interesan (No se porque en algunas posiciones muy concretas algunas posiciones toman valores raros)
		v_x[i]=v_y[i]=0;
	printf("\n\tNo es por nada, pero solo he tardado %0.15lf segundos \n\n\tEste es el camino seguido\n\n",time_maquina);
/*	for(i=0;i<L;i++)
		printf("(%i,%i),",v_x[i],v_y[i]);
	printf("\n");*/
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
	
int condiciones(int M[N][N],int xi,int yi){//Comprueba que en esa posicion no hay pared(-1) y no se sale de las dimensiones de la matriz
	if(xi>=0&&xi<N&&yi<N&&yi>=0&&M[xi][yi]!=-1)
		return 1;
	else 
		return 0;
}

void avanzar_4_sentidos(int M[N][N],int x,int y,int x_inicial,int y_inicial){// Función recursiva que repite una rama hasta que choque con una pared(-1), se salga de la matriz, haya una rama más corta que llega a la meta o se corte con una rama más corta para llegar a la meta

	if(M[x][y]==0||M[x_inicial][y_inicial]+1<M[x][y]){ //para que siga por esa rama, no se tiene que haber llegado a la meta o que vaya por un numero inferior al que hay en la meta
	
		if(condiciones(M,x_inicial-1,y_inicial)&&(M[x_inicial-1][y_inicial]==0||M[x_inicial][y_inicial]+1<M[x_inicial-1][y_inicial])){ // no avanzar si no se cumple la función condiciones o si hay un numero inferior en la casilla que va a ocupar
			M[x_inicial-1][y_inicial]=M[x_inicial][y_inicial]+1;//avanza una hacía abajo y suma uno al numero de pasos que se uso para llegar a la anterior
			avanzar_4_sentidos(M,x,y,x_inicial-1,y_inicial);
		}
		if(condiciones(M,x_inicial+1,y_inicial)&&(M[x_inicial+1][y_inicial]==0||M[x_inicial][y_inicial]+1<M[x_inicial+1][y_inicial])){
			M[x_inicial+1][y_inicial]=M[x_inicial][y_inicial]+1;
			avanzar_4_sentidos(M,x,y,x_inicial+1,y_inicial);
		}
		if(condiciones(M,x_inicial,y_inicial-1)&&(M[x_inicial][y_inicial-1]==0||M[x_inicial][y_inicial]+1<M[x_inicial][y_inicial-1])){
			M[x_inicial][y_inicial-1]=M[x_inicial][y_inicial]+1;		
			avanzar_4_sentidos(M,x,y,x_inicial,y_inicial-1);
		}
		if(condiciones(M,x_inicial,y_inicial+1)&&(M[x_inicial][y_inicial+1]==0||M[x_inicial][y_inicial]+1<M[x_inicial][y_inicial+1])){
			M[x_inicial][y_inicial+1]=M[x_inicial][y_inicial]+1;		
			avanzar_4_sentidos(M,x,y,x_inicial,y_inicial+1);
		}		
	}	
//	else{
//		system("cls");//borrar lo anteriro y imprime matriz
//		 imprime_matriz(M);
//	}

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

void comprobar(int M[N][N],int xi,int yi,int xf, int yf,int vector_x[L],int vector_y[L],int contador,int v_x[L],int v_y[L]){
	//Comprueba si hay una posición consecutiva con un número consecutivo mayor a esa posición y da como resultado los vectores v_x y v_y con la ruta más corta para llegar a la meta ejem primer punto de la ruta=M[v_x[0]][v_y[0]]
	int i;
	if(yi==yf&&xi==xf){// Si una rama llega a la meta será el camino más corto y aun que puede que haya más caminos serán igual de longitud
		for(i=0;i<L;i++){//Y ese camino se guardrá en v_x y v_y 
			v_x[i]=vector_x[i];
			v_y[i]=vector_y[i];
		}
	}
	else{
		contador++;
		if(M[xi+1][yi]==M[xi][yi]+1){//Comprobar si el número de abajo vale 1 más que el valor de esa posición
			vector_x[contador]=xi+1;
			vector_y[contador]=yi;
			comprobar(M,xi+1,yi,xf,yf,vector_x,vector_y,contador,v_x,v_y);//sigue comprobando en dicha posición (función recuersiva)
		}
		if(M[xi-1][yi]==M[xi][yi]+1){//arriba
			vector_x[contador]=xi-1;
			vector_y[contador]=yi;
			comprobar(M,xi-1,yi,xf,yf,vector_x,vector_y,contador,v_x,v_y);
		}
		if(M[xi][yi+1]==M[xi][yi]+1){//derecha
			vector_x[contador]=xi;
			vector_y[contador]=yi+1;
			comprobar(M,xi,yi+1,xf,yf,vector_x,vector_y,contador,v_x,v_y);
		}
		if(M[xi][yi-1]==M[xi][yi]+1){//izquierda
			vector_x[contador]=xi;
			vector_y[contador]=yi-1;
			comprobar(M,xi,yi-1,xf,yf,vector_x,vector_y,contador,v_x,v_y);
		}	
	}
}
int Pregunta(int v_x[L],int v_y[L],int x,int y,int *resta){
	int i,j=2;
	*resta=0;
	if(v_x[0]==0&&v_x[1]==0&&v_y[0]==0&&v_y[1]==0){// Si los vectores v_x y v_y aun están vacios que devuelva 2
	return 2;
	}
	else{
		for(i=0;i<L;i++){
			if(v_x[i]==x&&v_y[i]==y){// devuelve 2 si no está esa posición en los vectores y 1,-1 o 0 dependiendo de si se desplaza a la derecha, izquierda o (abajo o arriba) respectivamente
				j=v_y[i]-v_y[i-1];
				*resta=v_x[i]-v_x[i-1];
				break;
			}
		}
		return j;
	}
}
void imprime_matriz_con_flechas(int M[N][N],int v_x[L],int v_y[L]){
	int i,j,pregunta,resta_arriba=0;
	for(i=0;i<N;i++){
		printf("\t");
		for(j=0;j<N;j++){
			pregunta=Pregunta(v_x,v_y,i,j,&resta_arriba);
			if(M[i][j]==-1)//Si hay -1 en esta posicion que dibuje una X
				printf("  . ");
			else if(i==v_x[0]&&j==v_y[0])
				printf("  O ");
			else if(resta_arriba==1)
					printf("  v ");// simbolo flecha hacia arriba

				//printf("  %c ",193);// simbolo flecha hacia abajo
			else if(resta_arriba==-1)
				printf("  ^ ");
			//	printf("  %c ",194);// simbolo flecha hacia arriba
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
