// AHORCADO

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
typedef struct{
	char palabra[30];
}pal;
int numaleatorio(int n);
int ahorcado(char adivinapalabra[30], char cadena[30]);
void imprime_matriz(int M[][2], int f, int c);


void main(){

system("COLOR 2F");
	int aleatorio=0, longitud , i, intentos=6, fallos;
	pal peliculas[10]={"AVENGERS ENDGAME" , "TRANSFORMERS" , "HARRY POTTER" , "TITANIC" , "EL SENOR DE LOS ANILLOS" , "STAR WARS" , "GLADIADOR" , "JURASSIC PARK" , "EL CABALLERO OSCURO" , "TOY STORY"};
	pal series[10]={"JUEGO DE TRONOS" , "STRANGER THINGS" , "WESTWORLD" , "FRIENDS" , "COMO CONOCI A VUESTRA MADRE" , "LA QUE SE AVECINA" , "LA CASA DE PAPEL" , "PEAKY BLINDERS" , "EL PRINCIPE DE BEL AIR" , "THE BIG BANG THEORY"};
	pal musica[10]={"BOHEMIAN RHAPSODY" , "THRILLER" , "BOYS DONT CRY" , "WITH OR WITHOUT YOU" , "PURPURINA" , "LET IT BE" , "HEY BROTHER" , "VIVA LA VIDA" , "PAQUITO EL CHOCOLATERO" , "RAP GOD"};
	pal deportes[10]={"MICHAEL JORDAN" , "REAL MADRID" , "PADEL" , "JUANFRAN AL PALO" , "EL BICHO" , "MOHAMED ALI" , "CICLISMO" , "ESCALADA" , "RUGBY" , "PRESS BANCA"};
	char adivinapelicula[30];
	char adivinapalabra[30];
	char adivinamusica[30];
	char adivinadeporte[30];
	char letra;
	char letrausuario[30]=" ";

	int nofallos[2][2] = {{1,2}, {3,4}};

	char incognita[30];
	char categoria; //cat lo uso para seleccionar con un switch la categoría de la frase
	printf("Bienvenido al Ahorcado\n");
	system ("PAUSE");
	system("CLS");//esto lo pongo para que no imprima tanta información de golpe
	printf("En este juego el objetivo es adivinar la frase o palabra con el minimo numero de fallos\n");
	system("PAUSE"); 
	
	do{
	system("CLS");
	printf("Selecciona la categoria de la frase:\na.Peliculas\nb.Series\nc.Musica\nd.Deportes\n");
	scanf("%c", &categoria);


	
		switch(categoria){
			case 'a':
			case 'A':
				
				//char peliculas[10][1] = {"Avengers Endgame" , "Transformers" , "Harry Potter" , "Titanic" , "El senor de los anillos" , "Star Wars" , "Gladiator" , "Jurassic Park" , "El caballero oscuro" , "Toy Story"};
				system("CLS");
				printf("Has elegido la categoria de Peliculas\n");
				aleatorio = numaleatorio(10);
				printf("%s\n", peliculas[aleatorio]);
				strcpy(adivinapalabra, peliculas[aleatorio].palabra);
				printf("%s\n", adivinapalabra);
				i=0;
				while(1){
				
				fallos=ahorcado(peliculas[aleatorio].palabra, letrausuario);
				intentos-=fallos;
				printf("\n\n\nTe quedan %d intentos para adivinar la pelicula\n\n", intentos);
				printf(" _______\n/        |\n|\n|\n|\n|__\n");
				printf("Introduce una letra:\n");
				scanf(" %c", &letrausuario[i]);
				printf("%c", letra);
				system("CLS");				
				i++;
								
			}
					
					//aquí pondre la funcion del ahorcado general que accedera al fichero con los titulos de peliculas
				break;
				
			case 'b':
			case 'B':
				system("CLS");
				printf("Has elegido la categoria de Series\n");
				aleatorio = numaleatorio(10);
				printf("%s", series[aleatorio]);

					//aquí pondre la funcion del ahorcado general que accedera al fichero con los titulos de series
				break;
				
			case 'c':
			case 'C':
				system("CLS");
				printf("Has elegido la categoria de Musica\n");
				aleatorio = numaleatorio(10);
				printf("%s", musica[aleatorio]);

					//aquí pondre la funcion del ahorcado general que accedera al fichero con la musica
				break;
				
			case 'd':
			case 'D':
				system("CLS");
				printf("Has elegido la categoria de Deportes\n");
				aleatorio = numaleatorio(10);
				printf("%s", deportes[aleatorio]);
					//aquí pondre la funcion del ahorcado general que accedera al fichero con los deportes como jugadores famosos o equipos
				break;
				
			default:
			printf("Escoge una opcion valida\n");
			system("PAUSE");
			
			
			
				
		}
			

}while(1);

}


int numaleatorio(int n){
srand(time(NULL));
int i;
	i = rand()%n;
	return i;
}






int ahorcado(char adivinapalabra[30], char letrausuario[30]){
	int i, longitud, n, iguales, ganado=1, dif='A'-'a', error=1;
	
	longitud = strlen(adivinapalabra);
	

	for(i=0; i<longitud; i++){
		
		for(n=0, iguales=0; n<strlen(letrausuario); n++){
			if(letrausuario[n]==adivinapalabra[i]|| letrausuario[n]==adivinapalabra[i]-dif){
				iguales = 1;
			}
		}
			if(iguales==1){
				printf("%c ", adivinapalabra[i]);
				error=0;
			}
			else if(adivinapalabra[i]==' '){
						printf("   "); 
		}
			else{
				ganado=0;
					
		if(( adivinapalabra[i]>= 'A' &&  adivinapalabra[i]<= 'Z')){
						printf("_ ");	
		}
		
		if((adivinapalabra[i] >= 'a' && adivinapalabra[i] <= 'z')){
						printf("_ ");
		}
					
	}
				
	}
	if(ganado==1){
		printf("Has ganado");
		exit(0);
	}
	return error;
}


