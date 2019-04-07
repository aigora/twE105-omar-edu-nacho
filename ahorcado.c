// AHORCADO

#include <stdio.h>

void main(){
	char cat; //cat lo uso para seleccionar con un switch la categoría de la frase
	printf("Bienvenido al Ahorcado\n");
	system ("PAUSE");
	system("CLS");//esto lo pongo para que no imprima tanta información de golpe
	printf("En este juego el objetivo es adivinar la frase o palabra con el minimo numero de fallos\n");
	system("PAUSE"); 
	system("CLS");
	printf("Selecciona la categoria de la frase:\na.Peliculas\nb.Series\nc.Musica\nd.Deportes\n");
	scanf("%c", &cat);

		switch(cat){
		char pelicula1[] = "Avengers Endgame";
			case 'a':
			case 'A':
				system("CLS");
				printf("Has elegido la categoria de Peliculas\n");
				FILE *pf;   //lo uso para abrir un fichero con los titulos de peliculas
				pf = fopen("peliculas.txt", "w");
				if (pf==NULL){
					printf("No se ha podido acceder a los datos de las peliculas\n");
				
				}
				else
				fprintf(pf, "%s", pelicula1);
				
				fclose(pf);
					//aquí pondre la funcion del ahorcado general que accedera al fichero con los titulos de peliculas
				break;
				
			case 'b':
			case 'B':
				system("CLS");
				printf("Has elegido la categoria de Series\n");
					//aquí pondre la funcion del ahorcado general que accedera al fichero con los titulos de series
				break;
				
			case 'c':
			case 'C':
				system("CLS");
				printf("Has elegido la categoria de Musica\n");
					//aquí pondre la funcion del ahorcado general que accedera al fichero con la musica
				break;
				
			case 'd':
			case 'D':
				system("CLS");
				printf("Has elegido la categoria de Deportes\n");
					//aquí pondre la funcion del ahorcado general que accedera al fichero con los deportes como jugadores famosos o equipos
				break;
				
			default:
			printf("Escoge una opcion valida\n");
				
		}

	
}
