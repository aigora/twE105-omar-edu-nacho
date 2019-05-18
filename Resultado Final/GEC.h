/*
void avanzar_4_sentidos(int M[N][N],int coord_x,int coord_y,int,int,punto punto_camino[L],int v_x[L],int v_y[L],int contador);
void imprime_matriz_lab(int M[N][N]);
int Pregunta(int v_x[L],int v_y[L],int x,int y,int *resta);//Comprueba si una posici?n est? en los vectores (v_x,v_y)
void imprime_matriz_con_flechas(int M[N][N],int v_x[L],int v_y[L]);
void imprime_matriz_jugar(int M[N][N],int,int,int,int);//imprime matriz con O en la posicion x,y
int jugar_lab(int M[N][N],int,int,int,int);//controla como va a jugar el usuario
int condiciones(int M[N][N],int,int,int,int);
void Copiar_vector(int v1[L],int v2[L]);
void Puntuaciones(usuario lista_punt[D],FILE *leer);
*/
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define N 20 
#define L N*N 
#define D 20
#define d 10
#define E 30
typedef struct{
	int x,y;
}punto;
typedef struct{
	char palabra[E];
}pal;
typedef struct{
	char nombre[30];
	int punt;
}usuario;
typedef struct{//Estructura con coordenadas del punto y a cada punto va asociada una letra
	int x,y;
	char letra;
}punto_busca;
void laberinto(){
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
	{ 0, 0, 0,-1, 0, 0, 0, 0,-1,-1, 0, 0, 0, 0,-1, 0,-1, 0,-1, 0},
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
	}
	imprime_matriz_lab(mapa);
	srand(time(NULL));
	x_ini=rand()%N-1;
	y_ini=rand()%2;//Se eligen la posición inicial y la meta de forma aleatoria ( con condiciones)
	x_fin=rand()%N-1;
	y_fin=rand()%2+N-3;
	printf("\n\tTe atreves con el laberinto?");
	getch();
	mapa[x_ini][y_ini]=1;//Si hay pared(-1) en la posicion inicial o final, la quito 
	mapa[x_fin][y_fin]=0;
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
			imprime_matriz_jugar(mapa,v_x[i],v_y[i],x_fin,y_fin);
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

void imprime_matriz_lab(int M[N][N]){
	int i, j;
	printf("\t");
	for(i=1;i<=N;i++){
		if(i<10)
			printf(" ");//Se desalineban los n?meros de las columnas al ser de 2 digitos, as? se arregla
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
	printf("\n\tIntenta llegar por el camino mas corto:\n\n");
	printf("\tw=arriba\n\td=derecha\n\ts=abajo\n\ta=izquierda\n");
	imprime_matriz_jugar(mapa,xi,yi,xf,yf);
	int pasos=0;
	while(xi!=xf||yi!=yf){//Mientras no se alcanzo la meta
		switch(getch()){//Avanzar
			case 'W':
			case 'w'://arriba
				if(mapa[xi-1][yi]!=-1&&xi-1>=0){//Si no hay menos uno en esa posici?n (pared) y que no se salga de la matriz
					xi--;//se mueve hacía la arriba si se cumplen las condiciones
					system("cls");
					imprime_matriz_jugar(mapa,xi,yi,xf,yf);
					pasos++;//Aumenta número depasos
				}
				break;
			case 'S':
			case 's'://abajo
				if(mapa[xi+1][yi]!=-1&&xi+1<=N-1){//Las mismas condiciones que el if de antes
					xi++;
					system("cls");
					imprime_matriz_jugar(mapa,xi,yi,xf,yf);
					pasos++;
				}
				break;
			case 'D':
			case 'd'://derecha
				if(mapa[xi][yi+1]!=-1&&yi+1<=N-1){//Igual
					yi++;
					system("cls");
					imprime_matriz_jugar(mapa,xi,yi,xf,yf);
					pasos++;
				}
				break;
			case 'A':
			case 'a'://izquierda
				if(mapa[xi][yi-1]!=-1&&yi-1>=0){//Igual
					yi--;
					system("cls");
					imprime_matriz_jugar(mapa,xi,yi,xf,yf);
					pasos++;
				}
				break;
			default:
				printf("No valido ");
		}	
	}
	return pasos;
}

void imprime_matriz_jugar(int M[N][N],int xi,int yi,int xf,int yf){//(xi,yi) posición actual (O) y (xf,yf) meta (M)
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


//////////////////BuscaMInas//////////////////

void buscaminas(){
	empezar:
	system("color f9");
	FILE *agregar_archivo=fopen("puntuacion_buscaminas.txt","a");
	if(agregar_archivo==NULL){
		printf("error");
	}
	char letra,letras[d*d],Nickname[20];
	usuario lista_punt[30]={{"iniciamos",0}};
	int random,bombas=0,Mapa[d][d]={0,0,0},fila,columna,num_puntos=0,x,y,i,banderas_usadas,Pregunta_esta,nivel,dif='A'-'a',Puntuacion;
	float t1,t2,tiempo;
	punto_busca puntos[d*d]={0,0,0};//vector de la estructura punto
	printf("\n\tPon 1, 2 o 3 para eligir el nivel ");
	scanf("%i",&nivel);//Elige el nivel 1,2 o 3
	if(nivel==1)nivel=2;
	else if(nivel==2)nivel=3;
	else if(nivel==3)nivel=5;
	else goto empezar;
	system("cls");
	bombas=crear_buscaminas(Mapa,nivel);//Devuelve el número de bombas del mapa
	jugar(Mapa,puntos,0);//Imprime mapa
	printf("\nHay %i bombas\n\nHay que poner las coordenadas y despues A o B\n\n-A es para abrir casilla \n\n-B para poner bandera\n\nEjem: 1 1 A\n\n",bombas);
	t1=clock();//empieza a contar el tiempo
	do{
		scanf("%i %i %c",&x,&y,&letra);//EScanea posición (x,y) y letra si es B=poner bandera y A=abrir casilla
		x--;y--;// se resta uno porque el mapa va de 1 a d, y la matriz va de 0 a d-1
		if(banderas_usadas>=bombas&&letra=='B'){//Si usa más banderas que el número de bombas que hay
			printf("Si quieres usar mas banderas, quita alguna usada\nVuelve a introducir las coordenadas y la letra\n");
			do{
				scanf("%i %i %c",&x,&y,&letra);
				x--;y--;
			}while(letra=='B'&&dentro_matriz(Mapa,x,y));
		}
		if(letra>='a'&&letra<='z')	letra+=dif;//Si la pone minuscula la pasa a mayuscula
		if(dentro_matriz(Mapa,x,y)==0||(letra!='A'&&letra!='B')){//Si las coordenadas no están en la matriz o puso una letra distinta de A y B
			printf("\nError\nEscribe las coordenadas de nuevo\n");
			do{
				scanf("%i %i %c",&x,&y,&letra);
				x--;y--;
				if(letra>='a'&&letra<='z')	letra+=dif;//Si la pone minuscula la pasa a mayuscula
			}while(dentro_matriz(Mapa,x,y)==0||(letra!='A'&&letra!='B'));
		}
		if(Mapa[x][y]==-1&&letra=='A'){
			system("cls");
			imprime_matriz(Mapa);
			printf("\n\tHas perdido");
			break;//Sale del Do-While
		}
		else{
			Pregunta_esta=esta_en_vector(puntos,num_puntos,x,y);//Ver si la coordenadas introducida en está en el vector puntos
			if(Pregunta_esta!=-1)
				puntos[Pregunta_esta].letra=letra;
			
			else{//si no está que lo añada a la estructura puntos
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
		goto empezar;
	}
}

void imprime_matriz(int M[d][d]){
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
			if(random<nivel){//Va recorriendo la matriz y generando números random, si son menores que "nivel" pone una bomba(-1) en esa posición
				Mapa[i][j]=-1;
				bombas++;
			}
		}
	}
	for(i=0;i<d;++i){
		for(j=0;j<d;j++){
			if(Mapa[i][j]!=-1)//No hay bomba en esa posición
				Mapa[i][j]=bombas_alrededor(Mapa,i,j);//Entonces pone en ella el número de bombas que hay alrededor
		}
	}
	return bombas;
}

bombas_alrededor(int M[d][d],int x,int y){//suma 1 a la variable bombas si hay una bomba tocando(aunque se por las esquinas) a la posición inicial
	int bombas=0,i,j;
	for(i=-1;i<=1;i++)
		for(j=-1;j<=1;j++)
			if(M[x+i][y+j]==-1&&dentro_matriz(M,x+i,y+j))	bombas++;//Si a su alrededor en esa casilla hay -1 y está en la matriz, suma uno al número de bombas
	return bombas;
}

int dentro_matriz(int M[d][d],int x,int y){
	if(x>=0&&x<d&&y>=0&&y<d)// si está dentro de la matriz que devuelva 1, sino que devuelva 0
		return 1;
	else 
		return 0;
}
	
int jugar(int M[d][d],punto_busca puntos[d*d],int num_puntos){
	int i,j,n,pintado=0,banderas=0,Pregunta_ganar=1;
	printf(" \t");
	for(i=1;i<=d;i++){// pintar números del 1 al D arriba
		if(i<10)	printf(" ");//Pone espacio para cuadrar el mapa
		printf(" %i ",i);
	}
	printf("\n\n");
	for(i=0;i<d;i++){
		printf("%i\t",i+1);// pintar los números del 1 al D en el lateral izquierdo
		for(j=0;j<d;j++){
			for(n=0,pintado=0;n<num_puntos;n++){
				if(i==puntos[n].x&&j==puntos[n].y){//Si este punto fue eligido por el usuario
					if(puntos[n].letra=='A')	printf("  %i ",M[i][j]);//Si ha eligido A (abrir), muestra el número
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
				Pregunta_ganar=0;//Si se dibuja un punto, significa que no está todo el mapa resuelto, por lo tanto, no ha ganado aun
			}//pero si no se dibuja ningun punto, significa que ya estña resuelta y devolverá -1
		}
		printf("\n");	
	}
	if(Pregunta_ganar==1)
		return -1;//-1 es ganar la partida
	return banderas;
}

void Expandir(int M[d][d],punto_busca pts[d*d],int *num_pts,int x,int y){
	int i,j;
	for(i=-1;i<=1;i++)
		for(j=-1;j<=1;j++)
			if(dentro_matriz(M,x+i,y+j)&&esta_en_vector(pts,*num_pts,x+i,y+j)==-1){//La última condición es para que no vuelva a agregar un el punto inicial
				agregar(pts,*num_pts,x+i,y+j);
				*num_pts+=1;//num_ptos es el número de puntso guardados en el vector puntos
				if(M[x+i][y+j]==0)	Expandir(M,pts,num_pts,x+i,y+j);//Se sigue expandiendo si hay un cero en esa posición
			}
}

void agregar(punto_busca pts[d*d],int num_pts,int x,int y){
	pts[num_pts].x=x;
	pts[num_pts].y=y;
	pts[num_pts].letra='A';
}

int esta_en_vector(punto_busca puntos[d*d],int num_ptos,int x,int y){//devuelve -1 si no está en el vector y si está devuelve el número de la posición
	int i;
	for(i=0;i<num_ptos;i++)//para comprobar que el punto ya está y solo se le cambia la letra (de A a B, o de B a A)
		if(puntos[i].x==x&&puntos[i].y==y)
			return i;
	return -1;
}
////////////AHorcado//////////////
	void Ahorcado(){
	empezar:
	system("COLOR 2F");
	int aleatorio=0;
	pal peliculas[10]={"AVENGERS ENDGAME" , "TRANSFORMERS" , "HARRY POTTER" , "TITANIC" , "EL SENOR DE LOS ANILLOS" , "STAR WARS" , "GLADIADOR" , "JURASSIC PARK" , "EL CABALLERO OSCURO" , "TOY STORY"};
	pal series[10]={"JUEGO DE TRONOS" , "STRANGER THINGS" , "WESTWORLD" , "FRIENDS" , "COMO CONOCI A VUESTRA MADRE" , "LA QUE SE AVECINA" , "LA CASA DE PAPEL" , "PEAKY BLINDERS" , "EL PRINCIPE DE BEL AIR" , "THE BIG BANG THEORY"};
	pal musica[10]={"BOHEMIAN RHAPSODY" , "THRILLER" , "BOYS DONT CRY" , "WITH OR WITHOUT YOU" , "PURPURINA" , "LET IT BE" , "HEY BROTHER" , "VIVA LA VIDA" , "PAQUITO EL CHOCOLATERO" , "RAP GOD"};
	pal deportes[10]={"MICHAEL JORDAN" , "REAL MADRID" , "PADEL" , "JUANFRAN AL PALO" , "EL BICHO" , "MOHAMED ALI" , "CICLISMO" , "ESCALADA" , "RUGBY" , "PRESS BANCA"};
	char letra;
	char letrausuario[E]=" ";

/*	printf("Bienvenido al Ahorcado\n");
	system ("PAUSE");
	system("CLS");
	printf("En este juego el objetivo es adivinar la frase o palabra con el minimo numero de fallos\n");
	system("PAUSE"); 
	system("CLS");*/
	printf("Selecciona la categoria de la frase:\na.Peliculas\nb.Series\nc.Musica\nd.Deportes\n");
		switch(getch()){
			case 'a':
			case 'A':
				system("CLS");
				printf("Has elegido la categoria de Peliculas\n");
				aleatorio = numaleatorio(10);
				principal(peliculas[aleatorio].palabra, letrausuario);
				break;
				
			case 'b':
			case 'B':
				system("CLS");
				printf("Has elegido la categoria de Series\n");
				aleatorio = numaleatorio(10);
				principal(series[aleatorio].palabra, letrausuario);
				break;
				
			case 'c':
			case 'C':
				system("CLS");
				printf("Has elegido la categoria de Musica\n");
				aleatorio = numaleatorio(10);
				principal(musica[aleatorio].palabra, letrausuario);
				break;
				
			case 'd':
			case 'D':
				system("CLS");
				printf("Has elegido la categoria de Deportes\n");
				aleatorio = numaleatorio(10);
				principal(deportes[aleatorio].palabra, letrausuario);
				break;
				
			default:
			printf("Escoge una opcion valida\n");
			system("PAUSE");		
		}
		printf("\n Quieres jugar de nuevo? Pulsa 1:");
		if(getch()=='1') {
			system("cls");
		goto empezar;
	}
}	
	
	


void principal(char adivinapalabra[30], char cadena[30]){
	int intentos=7, fallos=0, i, puntuacion,si_perdido;
	i=0;
	char nombre[20]="";
	usuario lista_puntuaciones[E]={{"iniciar",0}};
	FILE *agregar=fopen("puntuacion_ahorcado.txt","a");
		if(agregar==NULL){
		printf("\n\t Error");
		exit(1);
	}
	float t1=clock(), t2, tiempo_total;
	while(1){
		fallos=ahorcado(adivinapalabra, cadena);
		if(fallos==-1){
			printf("\nHAS GANADO!!\n");
			t2=clock();
			tiempo_total = (t2-t1)/CLOCKS_PER_SEC;
			puntuacion=1000000/(int)tiempo_total*intentos;
			printf("Has tardado %f\nTu puntuacion ha sido de %i\n", tiempo_total, puntuacion);
			printf("Pon Nickname:\n");
			scanf(" %[^\n]", nombre);
			fprintf(agregar, "%s.%i\n", nombre, puntuacion);
			fclose(agregar);
			FILE *leer=fopen("puntuacion_ahorcado.txt","r");
			Puntuaciones(lista_puntuaciones, leer);
			break;
		}
		intentos-=fallos;
		printf("\n\n");
		si_perdido=imprime_ahorcado(intentos);
		if(si_perdido==1) break;
		printf("\nLas letras introducidas que llevas son: %s\n", cadena);
		printf("Introduce una letra:\n");
		cadena[i]=getch();
		system("CLS");				
		i++;					
	}
}

int numaleatorio(int n){
srand(time(NULL));
int i;
	i = rand()%n;
	return i;
}

int ahorcado(char adivinapalabra[30], char letrausuario[30]){
	
	int i, n,Pregunta_fallo, iguales, ganado=1, dif='A'-'a',ultima_letra_usuario=strlen(letrausuario);
	
	for(i=0; adivinapalabra[i]!='\0'; i++){
		
		for(n=0, iguales=0; n<ultima_letra_usuario; n++){
			if(letrausuario[n]==adivinapalabra[i] || letrausuario[n]==adivinapalabra[i]-dif){
				iguales = 1;
			}
		}
		if(iguales==1){
			printf("%c ", adivinapalabra[i]);
		}
		else if(adivinapalabra[i]==' '){
			printf("   "); 
		}
		else{
			ganado=0;
					
			if( adivinapalabra[i]>= 'A' &&  adivinapalabra[i]<= 'Z'){
				printf("_ ");	
			}
		
			if(adivinapalabra[i] >= 'a' && adivinapalabra[i] <= 'z'){
				printf("_ ");
			}
		}
	}
	if(ganado==1){
		//printf("\nHAS GANADO!!");
		return -1;
	}
	if(strlen(adivinapalabra)!=1)//Para que no empiece a comprobar si hay algún fallo antes de que el vector tenga contenido
		for(i=0,Pregunta_fallo=1;adivinapalabra[i]!='\0';i++)
			if(letrausuario[ultima_letra_usuario-1]==adivinapalabra[i] || letrausuario[ultima_letra_usuario-1]==adivinapalabra[i]-dif)
				Pregunta_fallo=0;
		
	return Pregunta_fallo;
}
int imprime_ahorcado(int intentos){
	if(intentos==7){
	printf("Te quedan %d intentos\n\n", intentos);
				printf(" _______\n/        |\n|\n|\n|\n|\n|\n|__\n");	
	}
	if(intentos==6){
	printf("Te quedan %d intentos\n\n", intentos);
				printf(" _______\n/        |\n|      (x_x)\n|\n|\n|\n|\n|__\n");	
	}
	if(intentos==5){
	printf("Te quedan %d intentos\n\n", intentos);
				printf(" _______\n/        |\n|      (x_x)\n|        |\n|\n|\n|\n|__\n");
	}
	if(intentos==4){
	printf("Te quedan %d intentos\n\n", intentos);
				printf(" _______\n/        |\n|      (x_x)\n|       _| \n|       \n|\n|\n|__\n");
	}																			
	if(intentos==3){																				 
	printf("Te quedan %d intentos\n\n", intentos);					 
				printf(" _______\n/        |\n|      (x_x)\n|       _|_ \n|       \n|\n|\n|__\n");
			}
				
	if(intentos==2){
	printf("Te quedan %d intentos\n\n", intentos);
				printf(" _______\n/        |\n|      (x_x)\n|       _|_ \n|        |\n|\n|\n|__\n");
	}
	if(intentos==1){
	printf("Te quedan %d intentos\n\n", intentos);
				printf(" _______\n/        |\n|      (x_x)\n|       _|_ \n|        | \n|       |  \n|\n|__\n");
	}
	if(intentos==0){
				printf(" _______\n/        |\n|      (x_x)\n|       _|_ \n|        | \n|       | |\n|\n|__\n");
	printf("HAS PERDIDO :(\n");	
	return 1;
	}
	return 0;
}


