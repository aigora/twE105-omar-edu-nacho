#include<stdio.h>
#include <time.h>
#define N 20 //dimension matriz cuadrada
#define L N*N //dimension vectores
#define D 20//Dimension del vector de usuarios (esctructura)
typedef struct{
	int x,y;
}punto;
typedef struct{
	char nombre[30];
	int punt;
}usuario;
void avanzar_4_sentidos(int M[N][N],int coord_x,int coord_y,int,int,punto punto_camino[L],int v_x[L],int v_y[L],int contador);
int Pregunta(int v_x[L],int v_y[L],int x,int y,int *resta);//Comprueba si una posici?n est? en los vectores (v_x,v_y)
void imprime_matriz_con_flechas(int M[N][N],int v_x[L],int v_y[L]);
void imprime_matriz_lab(int M[N][N],int,int,int,int);//imprime matriz con O en la posicion x,y
int jugar_lab(int M[N][N],int,int,int,int);//controla como va a jugar el usuario
int condiciones(int M[N][N],int,int,int,int);
void Copiar_vector(int v1[L],int v2[L]);
void Puntuaciones(usuario lista_punt[D],FILE *leer);
int main (){
	empezar_de_nuevo:
	system("color f0");
	punto puntos_camino[L];
	int x_fin,y_fin,x_ini,y_ini,i,pasos_usuario=0,pasos_maquina,v_x[L]={0},v_y[L]={0},j,Puntuacion,mapa[N][N]={
	{ 0, 0, 0,-1,-1,-1,-1, 0, 0, 0,-1,-1,-1,-1, 0, 0,-1, 0, 0, 0},
	{-1,-1, 0, 0, 0, 0,-1, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1, 0},
	{-1,-1,-1,-1,-1, 0,-1, 0,-1,-1, 0,-1,-1, 0,-1, 0,-1, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1,-1,-1,-1, 0,-1, 0,-1, 0},
	{ 0,-1,-1, 0,-1,-1,-1, 0,-1, 0, 0, 0, 0, 0, 0, 0,-1, 0,-1, 0},
	{ 0, 0, 0, 0, 0, 0,-1, 0, 0, 0,-1,-1,-1,-1,-1, 0,-1, 0,-1, 0},
	{-1, 0,-1,-1, 0,-1,-1, 0,-1, 0, 0,-1,-1,-1,-1, 0,-1, 0,-1, 0},
	{ 0, 0, 0,-1, 0, 0, 0, 0,-1,-1, 0, 0, 0, 0,-1, 0,-1, 0, 0, 0},
	{-1,-1,-1,-1,-1,-1,-1, 0,-1, 0,-1,-1,-1, 0,-1,-1,-1, 0,-1, 0},
	{ 0, 0, 0, 0, 0, 0,-1, 0, 0, 0,-1,-1,-1, 0, 0, 0,-1, 0,-1, 0},
	{ 0, 0, 0,-1,-1,-1,-1, 0,-1, 0, 0, 0, 0,-1,-1, 0,-1, 0,-1, 0},
	{-1,-1, 0, 0, 0, 0, 0, 0,-1, 0, 0,-1, 0, 0,-1, 0,-1, 0,-1, 0},
	{-1,-1,-1,-1,-1, 0,-1,-1,-1, 0,-1,-1, 0,-1,-1, 0,-1, 0,-1, 0},
	{ 0, 0, 0, 0, 0, 0,-1, 0, 0,-1,-1,-1, 0, 0,-1, 0,-1, 0,-1, 0},
	{ 0,-1,-1, 0,-1,-1,-1, 0,-1, 0, 0, 0, 0,-1,-1, 0,-1, 0,-1, 0},
	{ 0, 0, 0, 0, 0, 0,-1, 0, 0, 0,-1,-1, 0,-1,-1, 0,-1, 0,-1, 0},
	{-1, 0,-1,-1, 0,-1, 0, 0,-1, 0,-1,-1, 0, 0,-1, 0,-1, 0,-1, 0},
	{ 0, 0, 0,-1, 0, 0, 0, 0,-1, 0,-1, 0,-1, 0,-1, 0, 0, 0,-1, 0},
	{-1,-1,-1,-1,-1, 0,-1,-1,-1, 0, 0, 0,-1, 0,-1, 0,-1, 0,-1, 0},
	{ 0, 0, 0, 0, 0, 0,-1, 0, 0, 0,-1,-1,-1, 0,-1, 0,-1, 0,-1, 0},
	};
	float ti,tf,time_usuario;
	char Nickname[30];
	usuario lista_punt[D]={{"iniciar",0}};
	FILE *agregar_archivo=fopen("puntuacion_laberinto.txt","a");
	if(agregar_archivo==NULL){
		printf("\n\t Error");
		return 1;
	}
	srand(time(NULL));
	x_ini=rand()%N;
	y_ini=rand()%3;//Se eligen la posición inicial y la meta de forma aleatoria ( con condiciones)
	x_fin=rand()%N;
	y_fin=rand()%3+N-3;
	mapa[x_ini][y_ini]=1;//Si hay pared(-1) en la posicion inicial o final, la quito 
	mapa[x_fin][y_fin]=0;
	imprime_matriz_lab(mapa,x_ini,y_ini,x_fin,y_fin);
	printf("\tTe atreves con el laberinto?\n\n\tTienes que ir con La O a la M");
	printf("\n\tIntenta llegar por el camino mas corto:\n\n");
	printf("\tw=arriba\n\td=derecha\n\ts=abajo\n\ta=izquierda\n");
	getch();
	ti=clock();
	pasos_usuario=jugar_lab(mapa,x_ini,y_ini,x_fin,y_fin);//En esta función juega el usuario y devuelve los pasos que ha hecho
	tf=clock();
	time_usuario=(tf-ti)/(double)CLOCKS_PER_SEC;
	system("cls");
	printf("\n\tHas tardado %f segundos y lo has hecho en %i pasos",time_usuario,pasos_usuario);
	printf("\n\n\tLa verdad pensaba que no lo ibas a lograr\n\n");
	getch();	
	printf("\tBueno, Ahora me toca a mi, que los humanos sois muy lentos para estas cosas");
	getch();
	
	puntos_camino[0].x=x_ini;//Las coordenadnas del camino más corto se guardarán por orden en ese vector
	puntos_camino[0].y=y_ini;
	avanzar_4_sentidos(mapa,x_fin,y_fin,x_ini,y_ini,puntos_camino,v_x,v_y,1);//La maquina resuelve el laberinto
	printf("\n\n");
	pasos_maquina=mapa[x_fin][y_fin]-1;
	system("cls");
	printf("\n\tEl camino mas corto es de %i pasos\n",pasos_maquina);	
	printf("\n\tEste es el camino seguido\n\n");
	i=0;
	ti=clock();
	while(v_x[i-1]!=x_fin||v_y[i-1]!=y_fin){//Mientras no se llegá a la meta
		tf=clock();
		if((tf-ti)/CLOCKS_PER_SEC>0.1){//Es decir tiempo entre pasos es al menos de 0.1 segundos
			ti=clock();
			system("cls");
			imprime_matriz_lab(mapa,v_x[i],v_y[i],x_fin,y_fin);
			i++;
		}
	}
	system("cls");
	imprime_matriz_con_flechas(mapa,v_x,v_y);
	
	Puntuacion=1000000/((pasos_usuario+1-pasos_maquina)*((int)time_usuario+1));//Fórmula para calcular la puntuación
	if(pasos_usuario==pasos_maquina)
		Puntuacion+=50000;////Bonus si se sigue el camino más corto
	printf("\n\n\tTU PUNTUACION ES %i\n\n\tPara guardar partdia pulsa 1: ",Puntuacion);
	if(getch()=='1'){
		printf("\n\n\tPon Nickname: ");
		scanf(" %[^\n]",Nickname);
		fprintf(agregar_archivo,"%s.%i\n",Nickname,Puntuacion);//Se guarda la puntuacion
		i=0;
		fclose(agregar_archivo);//Se cierra y se abre en modo lectura, ya que de esta forma leerá la puntuación que acaba de leer el usuario
		FILE *leer_archivo=fopen("puntuacion_laberinto.txt","r");
	//	while(fscanf(leer_archivo,"%[^.].%i\n",lista_punt[i].nombre,&lista_punt[i].punt)!=EOF)
	//		i++;
		Puntuaciones(lista_punt,leer_archivo);
		fclose(leer_archivo);
	}
	
	printf("\n\n\tQuieres seguir jugado? Pulsa 1:");
	if(getch()=='1'){
		system("cls");
		goto empezar_de_nuevo;
	}
	printf("\n\n\tHasta la proxima");
	return 0;
}

int condiciones(int M[N][N],int xi,int yi,int xf,int yf){//Para que devuelva 1 no tiene que haber pared(-1) en la posici?n a la que se mueve y no se sale de las dimensiones de la matriz
	if(xf>=0&&xf<N&&yf<N&&yf>=0&&M[xf][yf]!=-1 && (M[xf][yf]==0 || M[xi][yi]+1<M[xf][yf]))//Y tambi?n en la posici?n en la que se va a avanzar tiene que haber un cero o que se va a mejorar al menos por uno al n?mero que ya hay all?
		return 1;
	else 
		return 0;
}

void avanzar_4_sentidos(int M[N][N],int x,int y,int x_inicial,int y_inicial,punto puntos_camino[L],int v_x[L],int v_y[L],int contador){//Función recursiva que repite una rama hasta que choque con una pared(-1), se salga de la matriz, haya una rama más corta que llega a la meta o se corte con una rama más corta para llegar a la meta

	if(M[x][y]==0||M[x_inicial][y_inicial]+1<M[x][y]){//para que siga por esa rama, no se tiene que haber llegado a la meta o que vaya por un numero inferior al que hay en la meta
	
		if(condiciones(M,x_inicial,y_inicial,x_inicial-1,y_inicial)){
			M[x_inicial-1][y_inicial]=M[x_inicial][y_inicial]+1;//avanza una hacía abajo y suma uno al numero de pasos que se uso para llegar a la anterior
			puntos_camino[contador].x=x_inicial-1;
			puntos_camino[contador].y=y_inicial;//Las posiciones por las que se expande se guardan en vector_x y vector_y, en la posici?n contador
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
	if(x_inicial==x&&y_inicial==y){//cuando est? en la meta, guarda el camino recorrido en v_x y v_y, el programa est? hecho de forma que solo puede llegar a la meta, mejorando el camino anterior
		int i;//Por lo que se acabar? guardando el camino m?s corto
		for(i=contador;i<L;i++)//Antes de pasar el camino a v_x y v_y, se limpia lo que se guard? en las siguientes posiciones a la que se llego a la meta 
			puntos_camino[i].x=puntos_camino[i].y=0;
		for(i=0;i<L;i++){//Copiando el camio en los vectores v_x y v_y
			v_x[i]=puntos_camino[i].x;
			v_y[i]=puntos_camino[i].y;
		}
	}
}

int Pregunta(int v_x[L],int v_y[L],int x,int y,int *resta_x){//Resta las coord de una posición con la anterior (Del camino más corto)
	int i,resta_y=0;
	*resta_x=0;
	for(i=0;i<L;i++){
		if(v_x[i]==x&&v_y[i]==y){//Si ese punto está en los vectores v_x y v_y
			resta_y=v_y[i]-v_y[i-1];//Resta la coord y de una posición y la anterior
			*resta_x=v_x[i]-v_x[i-1];//Resta la coord x de una posición x la anterior
			break;
		}//resta_x devuelve 1 (abajo), -1(arriba) y 0 (no cambia de fila)
	}	 //resta_y devuelve 1 (derecha), -1(izq) y 0 (no cambia de columna)
	return resta_y;
}
void imprime_matriz_con_flechas(int M[N][N],int v_x[L],int v_y[L]){
	int i,j,resta_fila,resta_columna=0;
	for(i=0;i<N;i++){
		printf("\t");
		for(j=0;j<N;j++){
			if(i!=0||j!=0)
				resta_fila=Pregunta(v_x,v_y,i,j,&resta_columna);
			if(M[i][j]==-1)//Si hay -1 en esta posicion que dibuje una X
				printf("  . ");
			else if(i==v_x[0]&&j==v_y[0])//Posición inicial
				printf("  O ");
			else if(resta_columna==1)
					printf("  v ");
			else if(resta_columna==-1)
				printf("  ^ ");
			else if(resta_fila==1)
				printf("  > ");
			else if(resta_fila==-1)
				printf("  < ");
			else
				printf("  . ");
		}
		printf("\n");
	}
}

int jugar_lab(int mapa[N][N],int xi,int yi,int xf,int yf){
	system("cls");
	imprime_matriz_lab(mapa,xi,yi,xf,yf);
	int pasos=0;
	while(xi!=xf||yi!=yf){//Mientras no se alcanzo la meta
		switch(getch()){//Avanzar
			case 'W':
			case 'w'://arriba
				if(mapa[xi-1][yi]!=-1&&xi-1>=0){//Si no hay menos uno en esa posici?n (pared) y que no se salga de la matriz
					xi--;//se mueve hacía la arriba si se cumplen las condiciones
					system("cls");
					imprime_matriz_lab(mapa,xi,yi,xf,yf);
					pasos++;//Aumenta número depasos
				}
				break;
			case 'S':
			case 's'://abajo
				if(mapa[xi+1][yi]!=-1&&xi+1<=N-1){//Las mismas condiciones que el if de antes
					xi++;
					system("cls");
					imprime_matriz_lab(mapa,xi,yi,xf,yf);
					pasos++;
				}
				break;
			case 'D':
			case 'd'://derecha
				if(mapa[xi][yi+1]!=-1&&yi+1<=N-1){//Igual
					yi++;
					system("cls");
					imprime_matriz_lab(mapa,xi,yi,xf,yf);
					pasos++;
				}
				break;
			case 'A':
			case 'a'://izquierda
				if(mapa[xi][yi-1]!=-1&&yi-1>=0){//Igual
					yi--;
					system("cls");
					imprime_matriz_lab(mapa,xi,yi,xf,yf);
					pasos++;
				}
				break;
			default:
				printf("No valido ");
		}	
	}
	return pasos;
}

void imprime_matriz_lab(int M[N][N],int xi,int yi,int xf,int yf){//(xi,yi) posición actual (O) y (xf,yf) meta (M)
	int i, j;
	printf("\n");
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++){
			if(i==xi&&j==yi)// dibuja O en la posicion actual
				printf("  O ");
			else if(M[i][j]==-1)//X en pared
				printf("  X ");
			else if(i==xf&&j==yf)// dibuja M en la meta
				printf("  M ");
			else
				printf("  . ");
			}
		printf("\n");
	}
}
void Puntuaciones(usuario lista_punt[D],FILE *leer_archivo){//Ordena el vector de usuarios de mayor (en la posición 0) a menor
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

