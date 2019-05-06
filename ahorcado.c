// AHORCADO

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
typedef struct{
	char palabra[30];
}pal;
void principal(char adivinapalabra[30], char cadena[30]);
int numaleatorio(int n);
int ahorcado(char adivinapalabra[30], char cadena[30]);
void imprime_ahorcado(int intentos);


void main(){

system("COLOR 2F");
	int aleatorio=0;
	pal peliculas[10]={"AVENGERS ENDGAME" , "TRANSFORMERS" , "HARRY POTTER" , "TITANIC" , "EL SENOR DE LOS ANILLOS" , "STAR WARS" , "GLADIADOR" , "JURASSIC PARK" , "EL CABALLERO OSCURO" , "TOY STORY"};
	pal series[10]={"JUEGO DE TRONOS" , "STRANGER THINGS" , "WESTWORLD" , "FRIENDS" , "COMO CONOCI A VUESTRA MADRE" , "LA QUE SE AVECINA" , "LA CASA DE PAPEL" , "PEAKY BLINDERS" , "EL PRINCIPE DE BEL AIR" , "THE BIG BANG THEORY"};
	pal musica[10]={"BOHEMIAN RHAPSODY" , "THRILLER" , "BOYS DONT CRY" , "WITH OR WITHOUT YOU" , "PURPURINA" , "LET IT BE" , "HEY BROTHER" , "VIVA LA VIDA" , "PAQUITO EL CHOCOLATERO" , "RAP GOD"};
	pal deportes[10]={"MICHAEL JORDAN" , "REAL MADRID" , "PADEL" , "JUANFRAN AL PALO" , "EL BICHO" , "MOHAMED ALI" , "CICLISMO" , "ESCALADA" , "RUGBY" , "PRESS BANCA"};
	char letra;
	char letrausuario[30]=" ";
	char categoria; 
	printf("Bienvenido al Ahorcado\n");
	system ("PAUSE");
	system("CLS");
	printf("En este juego el objetivo es adivinar la frase o palabra con el minimo numero de fallos\n");
	system("PAUSE"); 
	system("CLS");
	printf("Selecciona la categoria de la frase:\na.Peliculas\nb.Series\nc.Musica\nd.Deportes\n");
	scanf("%c", &categoria);


	
		switch(categoria){
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
}	
	
	


void principal(char adivinapalabra[30], char cadena[30]){
	int intentos=7, fallos=0, i;
	i=0;
	cadena[0]='\0';
	while(1){
		fallos=ahorcado(adivinapalabra, cadena);
		intentos-=fallos;
		printf("\n\n");
		imprime_ahorcado(intentos);
		printf("\nLas letras introducidas que llevas son: %s\n", cadena);
		printf("Introduce una letra:\n");
		scanf(" %c", &cadena[i]);
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
		printf("\nHAS GANADO!!");
		exit(0);
	}

		for(i=0,Pregunta_fallo=1;adivinapalabra[i]!='\0';i++){
			if(letrausuario[ultima_letra_usuario-1]==adivinapalabra[i] || letrausuario[ultima_letra_usuario-1]==adivinapalabra[i]-dif)
				Pregunta_fallo=0;
		}
		return Pregunta_fallo;
}
void imprime_ahorcado(int intentos){
	if(intentos==7){
	printf("Te quedan %d intentos para adivinar la pelicula\n\n", intentos);
				printf(" _______\n/        |\n|\n|\n|\n|\n|\n|__\n");	
	}
	if(intentos==6){
	printf("Te quedan %d intentos para adivinar la pelicula\n\n", intentos);
				printf(" _______\n/        |\n|      (x_x)\n|\n|\n|\n|\n|__\n");	
	}
	if(intentos==5){
	printf("Te quedan %d intentos para adivinar la pelicula\n\n", intentos);
				printf(" _______\n/        |\n|      (x_x)\n|        |\n|\n|\n|\n|__\n");
	}
	if(intentos==4){
	printf("Te quedan %d intentos para adivinar la pelicula\n\n", intentos);
				printf(" _______\n/        |\n|      (x_x)\n|       _| \n|       \n|\n|\n|__\n");
	}																			
	if(intentos==3){																				 
	printf("Te quedan %d intentos para adivinar la pelicula\n\n", intentos);					 
				printf(" _______\n/        |\n|      (x_x)\n|       _|_ \n|       \n|\n|\n|__\n");
			}
				
	if(intentos==2){
	printf("Te quedan %d intentos para adivinar la pelicula\n\n", intentos);
				printf(" _______\n/        |\n|      (x_x)\n|       _|_ \n|        |\n|\n|\n|__\n");
	}
	if(intentos==1){
	printf("Te quedan %d intentos para adivinar la pelicula\n\n", intentos);
				printf(" _______\n/        |\n|      (x_x)\n|       _|_ \n|        | \n|       |  \n|\n|__\n");
	}
	if(intentos==0){
				printf(" _______\n/        |\n|      (x_x)\n|       _|_ \n|        | \n|       | |\n|\n|__\n");
	printf("HAS PERDIDO :(\n");	
	exit(1);
	}
}


